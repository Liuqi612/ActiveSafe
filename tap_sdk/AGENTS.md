# TAP SDK Planning rules

Before any Planning work, read `../../PLANNING_PORTING_RULES.md` completely.

This repository owns the ported Planning core and `tap_adapter` boundary.

- Preserve unrelated existing changes.
- Keep upstream algorithm structure recognizable and traceable.
- Use explicit source lists; never recursively glob Planning production code.
- Keep RSCL message types outside the Planning core.
- Do not compile or link DLP-only or `aeb_restored_package` code.
- Remove all DLP-only runtime logic from shared files in the TAP copy while
  preserving DP, Interactive A*, DDP, validation, and Normal fallback behavior.
