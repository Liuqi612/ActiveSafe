#pragma once

#include <sys/stat.h>
#include <sys/types.h>

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

#include "common/log.h"
#include "math/vec.h"
#include "util/occ_ddp_debug_support.h"

namespace pnc_x {
namespace planning {

inline std::string OccDdpCsvDebugPath() {
    return "/home/sensetime/ws/pilot/senseauto_modules_pilot_planning/"
           "planning/debug_tools/occ_ddp_csv_debug/occ_ddp_debug.csv";
}

inline std::string OccDdpCsvDebugDirectory() {
    return "/home/sensetime/ws/pilot/senseauto_modules_pilot_planning/"
           "planning/debug_tools/occ_ddp_csv_debug";
}

inline std::string OccDdpCsvHeaderLine() {
    return "frame_id,stamp_us,local_time,layer,entity_id,point_idx,closed,"
           "reason,x,y,px,py,dx,dy";
}

inline std::mutex &OccDdpCsvMutex() {
    static std::mutex mutex;
    return mutex;
}

inline bool &OccDdpCsvSessionInitialized() {
    static bool initialized = false;
    return initialized;
}

inline bool EnsureOccDdpCsvDirectory(const std::string &dir) {
    if (dir.empty()) {
        return false;
    }
    std::string current;
    current.reserve(dir.size());
    if (dir.front() == '/') {
        current = "/";
    }
    for (size_t i = 0; i < dir.size(); ++i) {
        const char ch = dir[i];
        if (ch == '/') {
            if (!current.empty() && current != "/") {
                if (::mkdir(current.c_str(), 0755) != 0 && errno != EEXIST) {
                    LOG_WARN("[OccDdpCsvDebug] failed to create dir "
                             << current << ": " << std::strerror(errno));
                    return false;
                }
            }
            continue;
        }
        current.push_back(ch);
    }
    if (::mkdir(current.c_str(), 0755) != 0 && errno != EEXIST) {
        LOG_WARN("[OccDdpCsvDebug] failed to create dir "
                 << current << ": " << std::strerror(errno));
        return false;
    }
    return true;
}

inline void EnsureOccDdpCsvHeader(std::ofstream *ofs) {
    (*ofs) << OccDdpCsvHeaderLine() << "\n";
}

inline std::string FormatOccDdpCsvLocalTime(long long stamp_us) {
    if (stamp_us <= 0) {
        return "";
    }
    const std::time_t sec = static_cast<std::time_t>(stamp_us / 1000000LL);
    const int millis = static_cast<int>((stamp_us % 1000000LL) / 1000LL);
    std::tm tm_buf {};
    if (::localtime_r(&sec, &tm_buf) == nullptr) {
        return "";
    }
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%m-%d %H:%M:%S") << "."
        << std::setw(3) << std::setfill('0') << millis;
    return oss.str();
}

inline bool PrepareOccDdpCsvFile(const std::string &path, bool *need_header) {
    *need_header = true;
    struct stat st {};
    if (::stat(path.c_str(), &st) != 0) {
        return true;
    }
    if (st.st_size == 0) {
        return true;
    }

    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        LOG_WARN("[OccDdpCsvDebug] failed to read existing file " << path);
        return false;
    }
    std::string header_line;
    std::getline(ifs, header_line);
    if (header_line == OccDdpCsvHeaderLine()) {
        *need_header = false;
        return true;
    }

    const std::string legacy_path =
        path + ".legacy_" + std::to_string(static_cast<long long>(::time(nullptr)));
    if (::rename(path.c_str(), legacy_path.c_str()) != 0) {
        LOG_WARN("[OccDdpCsvDebug] failed to backup legacy csv " << path
                 << " -> " << legacy_path << ": " << std::strerror(errno));
        return false;
    }
    LOG_WARN("[OccDdpCsvDebug] backed up legacy csv schema to "
             << legacy_path << ", new rows will use header: "
             << OccDdpCsvHeaderLine());
    return true;
}

inline std::ofstream OpenOccDdpCsvAppend() {
    const std::string dir = OccDdpCsvDebugDirectory();
    if (!EnsureOccDdpCsvDirectory(dir)) {
        return std::ofstream();
    }

    const std::string path = OccDdpCsvDebugPath();
    const bool first_open_in_process = !OccDdpCsvSessionInitialized();
    bool need_header = false;
    if (!PrepareOccDdpCsvFile(path, &need_header)) {
        return std::ofstream();
    }

    std::ofstream ofs(
        path, first_open_in_process ? (std::ios::out | std::ios::trunc)
                                    : (std::ios::out | std::ios::app));
    if (!ofs.is_open()) {
        LOG_WARN("[OccDdpCsvDebug] failed to open " << path);
        return ofs;
    }
    ofs << std::fixed << std::setprecision(6);
    if (first_open_in_process || need_header) {
        EnsureOccDdpCsvHeader(&ofs);
    }
    OccDdpCsvSessionInitialized() = true;
    return ofs;
}

inline void WriteOccDdpCsvPoint(std::ofstream *ofs,
                                const OccDdpCsvFrameContext &ctx,
                                const std::string &layer,
                                const std::string &entity_id,
                                int point_idx,
                                int closed,
                                const char *reason_name,
                                double x,
                                double y,
                                double px,
                                double py,
                                double dx,
                                double dy) {
    (*ofs) << ctx.frame_id << "," << ctx.stamp_us << ","
           << FormatOccDdpCsvLocalTime(ctx.stamp_us) << "," << layer << ","
           << entity_id << "," << point_idx << "," << closed << ","
           << reason_name << "," << x << "," << y << "," << px << ","
           << py << "," << dx << "," << dy << "\n";
}

inline void WriteOccDdpCsvPolygon(const OccDdpCsvFrameContext &ctx,
                                  const std::string &layer,
                                  const std::string &entity_id,
                                  const std::vector<Vec2d> &points,
                                  bool closed,
                                  OccDdpCsvRejectReason reason) {
    if (!IsOccDebugEnabled() || ctx.frame_id < 0 || points.empty()) {
        return;
    }
    std::lock_guard<std::mutex> lock(OccDdpCsvMutex());
    std::ofstream ofs = OpenOccDdpCsvAppend();
    if (!ofs.is_open()) {
        return;
    }
    const char *reason_name = OccDdpCsvRejectReasonName(reason);
    for (size_t i = 0; i < points.size(); ++i) {
        WriteOccDdpCsvPoint(&ofs, ctx, layer, entity_id, static_cast<int>(i),
                            closed ? 1 : 0, reason_name, points[i].x(),
                            points[i].y(), 0.0, 0.0, 0.0, 0.0);
    }
}

inline void WriteOccDdpCsvPolyline(const OccDdpCsvFrameContext &ctx,
                                   const std::string &layer,
                                   const std::string &entity_id,
                                   const std::vector<Vec2d> &points) {
    WriteOccDdpCsvPolygon(ctx, layer, entity_id, points, false,
                          OccDdpCsvRejectReason::kNone);
}

inline void WriteOccDdpCsvSegment(const OccDdpCsvFrameContext &ctx,
                                  const std::string &layer,
                                  const std::string &entity_id,
                                  const Vec2d &start,
                                  const Vec2d &end,
                                  OccDdpCsvRejectReason reason) {
    if (!IsOccDebugEnabled() || ctx.frame_id < 0) {
        return;
    }
    std::lock_guard<std::mutex> lock(OccDdpCsvMutex());
    std::ofstream ofs = OpenOccDdpCsvAppend();
    if (!ofs.is_open()) {
        return;
    }
    const char *reason_name = OccDdpCsvRejectReasonName(reason);
    WriteOccDdpCsvPoint(&ofs, ctx, layer, entity_id, 0, 0, reason_name,
                        start.x(), start.y(), 0.0, 0.0, 0.0, 0.0);
    WriteOccDdpCsvPoint(&ofs, ctx, layer, entity_id, 1, 0, reason_name,
                        end.x(), end.y(), 0.0, 0.0, 0.0, 0.0);
}

inline void WriteOccDdpCsvArrow(const OccDdpCsvFrameContext &ctx,
                                const std::string &layer,
                                const std::string &entity_id,
                                double px,
                                double py,
                                double dx,
                                double dy) {
    if (!IsOccDebugEnabled() || ctx.frame_id < 0) {
        return;
    }
    std::lock_guard<std::mutex> lock(OccDdpCsvMutex());
    std::ofstream ofs = OpenOccDdpCsvAppend();
    if (!ofs.is_open()) {
        return;
    }
    WriteOccDdpCsvPoint(&ofs, ctx, layer, entity_id, 0, 0, "", 0.0, 0.0, px,
                        py, dx, dy);
}

}  // namespace planning
}  // namespace pnc_x
