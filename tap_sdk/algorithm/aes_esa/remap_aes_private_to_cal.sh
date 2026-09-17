#!/usr/bin/env bash
# -----------------------------------------------------------------------------
# 脚本名: remap_aes_private_to_cal.sh
#
# 作用:
#   在每次 Simulink 重新生成代码后，自动完成三件事：
#   1) 自动修复 AES_ESA_SWC_private.h 的读写权限/属主（必要时）
#   2) 将所有 "Expression: k_AES_*" 对应的 #define 右值重映射为 k_AES_*
#   3) 对二维 k_AES 表（仅 *_tableData）自动展平为 &k_AES_xxx[0][0]
#
# 说明:
#   - 仅处理 k_AES_*，不会改 k_LCG/k_ILC/k_LCK 等其它参数。
#   - 可重复执行（幂等），重复执行不会破坏结果。
#   - 第 3 步用于消除 look2_iflf_linlcapw 等场景下的二维表指针类型 warning 风险。
# -----------------------------------------------------------------------------
set -euo pipefail

usage() {
  cat <<'USAGE'
用法:
  remap_aes_private_to_cal.sh [private_header]

参数:
  private_header  可选，指定 AES_ESA_SWC_private.h 的绝对路径。
                  不传则自动按脚本所在目录推断默认路径。

默认路径优先级:
  1) <script_dir>/aes/AES_ESA_SWC_ert_rtw/AES_ESA_SWC_private.h
  2) <script_dir>/../module/tap_sdk/algorithm/aes_esa/aes/AES_ESA_SWC_ert_rtw/AES_ESA_SWC_private.h
USAGE
}

log_info() { echo "[INFO] $*"; }
log_warn() { echo "[WARN] $*"; }
log_err()  { echo "[ERROR] $*" >&2; }

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

# 1) 解析目标 private.h 路径
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
candidate_in_place="${script_dir}/aes/AES_ESA_SWC_ert_rtw/AES_ESA_SWC_private.h"
candidate_from_repo="$(cd "${script_dir}/.." && pwd)/module/tap_sdk/algorithm/aes_esa/aes/AES_ESA_SWC_ert_rtw/AES_ESA_SWC_private.h"

if [[ -n "${1:-}" ]]; then
  private_header="$1"
elif [[ -f "${candidate_in_place}" ]]; then
  private_header="${candidate_in_place}"
else
  private_header="${candidate_from_repo}"
fi

if [[ ! -f "${private_header}" ]]; then
  log_err "未找到目标文件: ${private_header}"
  exit 1
fi

private_dir="$(cd "$(dirname "${private_header}")" && pwd)"

# 2) 解析 AES_ESA_cal.h 路径（用于识别二维 k_AES_*）
cal_candidate_in_place="${script_dir}/aes/CAL/AES_ESA_cal.h"
cal_candidate_from_repo="$(cd "${script_dir}/.." && pwd)/module/tap_sdk/algorithm/aes_esa/aes/CAL/AES_ESA_cal.h"
cal_header=""
if [[ -f "${cal_candidate_in_place}" ]]; then
  cal_header="${cal_candidate_in_place}"
elif [[ -f "${cal_candidate_from_repo}" ]]; then
  cal_header="${cal_candidate_from_repo}"
fi

# 3) 自动修权限（必要时）
# 目标: 当前执行用户对目标文件可读写，对目标目录可写。
ensure_permissions() {
  if [[ -r "${private_header}" && -w "${private_header}" && -w "${private_dir}" ]]; then
    return 0
  fi

  local target_uid target_gid
  target_uid="${SUDO_UID:-$(id -u)}"
  target_gid="${SUDO_GID:-$(id -g)}"

  log_warn "检测到权限不足，尝试自动修复..."
  log_info "目标文件: ${private_header}"

  if [[ "$(id -u)" -eq 0 ]]; then
    # 以 root 运行时直接修复
    chown "${target_uid}:${target_gid}" "${private_header}" || true
    chmod u+rw,go+r "${private_header}" || true
    chown "${target_uid}:${target_gid}" "${private_dir}" || true
    chmod u+rwx "${private_dir}" || true
  else
    # 非 root 时尝试 sudo
    if ! command -v sudo >/dev/null 2>&1; then
      log_err "未找到 sudo，无法自动修权限。"
      return 1
    fi
    sudo chown "${target_uid}:${target_gid}" "${private_header}"
    sudo chmod u+rw,go+r "${private_header}"
    sudo chown "${target_uid}:${target_gid}" "${private_dir}"
    sudo chmod u+rwx "${private_dir}"
  fi

  if [[ ! -r "${private_header}" || ! -w "${private_header}" || ! -w "${private_dir}" ]]; then
    log_err "自动修权限后仍不可写，请手动检查属主与权限。"
    return 1
  fi
}

ensure_permissions

# 4) 在目标目录创建临时文件，避免跨文件系统 mv 问题
tmp_before="$(mktemp "${private_dir}/.remap_before.XXXXXX")"
tmp_after="$(mktemp "${private_dir}/.remap_after.XXXXXX")"
tmp_2d_list="$(mktemp "${private_dir}/.remap_2d.XXXXXX")"
cp "${private_header}" "${tmp_before}"

# 5) 确保 private.h 已包含 AES_ESA_cal.h（缺失时补充）
if ! grep -q '^#include "AES_ESA_cal.h"' "${private_header}"; then
  awk '
    BEGIN { inserted = 0 }
    {
      print $0
      if (inserted == 0 && $0 ~ /^#include "AES_ESA_SWC\.h"/) {
        print "#include \"AES_ESA_cal.h\""
        inserted = 1
      }
    }
  ' "${private_header}" > "${tmp_after}"
  mv "${tmp_after}" "${private_header}"
fi

# 6) 第一步 remap: 将 "Expression: k_AES_*" 的 #define 右值重映射到 k_AES_*
# 例:
#   #define rtCP_xxx rtCP_pooled_xxx /* Expression: k_AES_ABC
#   ->
#   #define rtCP_xxx k_AES_ABC       /* Expression: k_AES_ABC
perl -pe '
  s/^(\s*#define\s+\S+\s+)\S+(\s*\/\*\s*Expression:\s*(k_AES_[A-Za-z0-9_]+).*)$/$1$3$2/
' "${private_header}" > "${tmp_after}"
mv "${tmp_after}" "${private_header}"

# 7) 第二步 remap: 二维 k_AES_*（仅 *_tableData）展平为 &k_AES_xxx[0][0]
#   - 先从 AES_ESA_cal.h 收集所有二维 k_AES_* 名称
#   - 再只处理 private.h 中 *_tableData 的映射行
#   - 这样可以消除二维数组到一维指针的类型 warning
if [[ -n "${cal_header}" && -f "${cal_header}" ]]; then
  perl -ne '
    if (/\bfloat32\s+(k_AES_[A-Za-z0-9_]+)_str\s*\[\s*\d+\s*\]\s*\[\s*\d+\s*\]\s*;/) {
      print "$1\n";
    }
  ' "${cal_header}" | sort -u > "${tmp_2d_list}"

  if [[ -s "${tmp_2d_list}" ]]; then
    TWO_D_LIST="${tmp_2d_list}" perl -pe '
      BEGIN {
        my $f = $ENV{"TWO_D_LIST"};
        open my $fh, "<", $f or die "open $f failed: $!";
        while (<$fh>) {
          chomp;
          next unless length($_);
          $is2d{$_} = 1;
        }
      }

      if (/^(\s*#define\s+)(\S+)(\s+)([^\/\s][^\/]*?)(\s*\/\*\s*Expression:\s*(k_AES_[A-Za-z0-9_]+).*)$/) {
        my ($prefix, $macro, $space, $rhs, $tail, $expr) = ($1, $2, $3, $4, $5, $6);
        $rhs =~ s/\s+$//;

        if ($macro =~ /_tableData$/ && $rhs eq $expr && exists $is2d{$expr}) {
          $_ = $prefix . $macro . $space . "(&" . $expr . "[0][0])" . $tail . "\n";
        }
      }
    ' "${private_header}" > "${tmp_after}"
    mv "${tmp_after}" "${private_header}"
  else
    log_warn "未在 AES_ESA_cal.h 识别到二维 k_AES_*，跳过二维展平步骤。"
  fi
else
  log_warn "未找到 AES_ESA_cal.h，跳过二维展平步骤。"
fi

# 8) 统计与校验
total_k_aes_expr="$({ grep -cE '^#define[[:space:]]+[^[:space:]]+[[:space:]]+.*\/\*[[:space:]]*Expression:[[:space:]]*k_AES_' "${private_header}"; } || true)"
remaining_pool_k_aes="$({ grep -cE '^#define[[:space:]]+[^[:space:]]+[[:space:]]+rtCP_pooled_[^[:space:]]+[[:space:]]*\/\*[[:space:]]*Expression:[[:space:]]*k_AES_' "${private_header}"; } || true)"

if [[ -s "${tmp_2d_list}" ]]; then
  total_2d_table_targets="$(perl -e '
    my ($list, $priv) = @ARGV;
    my %two;
    open my $lf, "<", $list or die $!;
    while (<$lf>) { chomp; $two{$_} = 1 if $_ ne ""; }

    my $cnt = 0;
    open my $pf, "<", $priv or die $!;
    while (<$pf>) {
      if (/^#define\s+\S+_tableData\s+.*Expression:\s*(k_AES_[A-Za-z0-9_]+)/) {
        $cnt++ if exists $two{$1};
      }
    }
    print $cnt;
  ' "${tmp_2d_list}" "${private_header}")"

  remaining_unflattened_2d="$(perl -e '
    my ($list, $priv) = @ARGV;
    my %two;
    open my $lf, "<", $list or die $!;
    while (<$lf>) { chomp; $two{$_} = 1 if $_ ne ""; }

    my $cnt = 0;
    open my $pf, "<", $priv or die $!;
    while (<$pf>) {
      if (/^#define\s+\S+_tableData\s+(k_AES_[A-Za-z0-9_]+)\s*\/\*\s*Expression:\s*(k_AES_[A-Za-z0-9_]+)/) {
        my ($rhs, $expr) = ($1, $2);
        if ($rhs eq $expr && exists $two{$expr}) {
          $cnt++;
        }
      }
    }
    print $cnt;
  ' "${tmp_2d_list}" "${private_header}")"
else
  total_2d_table_targets=0
  remaining_unflattened_2d=0
fi

changed_lines="$(diff -u "${tmp_before}" "${private_header}" | grep -cE '^[+-]' || true)"

rm -f "${tmp_before}" "${tmp_after}" "${tmp_2d_list}"

echo "Remap 完成:"
echo "  文件: ${private_header}"
echo "  检测到的 k_AES 映射行数: ${total_k_aes_expr}"
echo "  仍使用 rtCP_pooled_ 的 k_AES 行数: ${remaining_pool_k_aes}"
echo "  二维 k_AES 目标 tableData 行数: ${total_2d_table_targets}"
echo "  仍未展平的二维 tableData 行数: ${remaining_unflattened_2d}"
echo "  本次变更行数(+/-): ${changed_lines}"

if [[ "${remaining_pool_k_aes}" != "0" ]]; then
  log_err "仍有部分 k_AES 映射未替换，请检查模型生成产物。"
  exit 2
fi

if [[ "${remaining_unflattened_2d}" != "0" ]]; then
  log_err "仍有二维 k_AES tableData 未展平，请检查映射规则。"
  exit 3
fi
