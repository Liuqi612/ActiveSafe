# Planning DLP Removal Audit

## Scope

The TAP Planning production target is the rule-based Emergency Planning closure.
Its runtime path is:

`Interactive A* (or DP) -> DDP -> ValidateTrajectory`.

DLP is outside this product scope. The target therefore removes DLP behavior
from shared files instead of retaining a mode flag that is always false.

## Removed from the Planning copy

- DLP trajectory input fields and mode selectors in
  `optimization/ddp/trajectory_optimizer_input.h`.
- DLP initial-trajectory projection, derivative repair, selected-input
  geometry checks, speed-reference guards, and DLP start-source reporting.
- DLP-only cost weighting, path-tracking gain changes, and fast-front object
  state carried across frames.
- `hold_pp`/`dlp_pp` side paths and DLP-specific fallback/adaptation limits.
- DLP-only adapter, motion-planner, occupancy-filter, and task files. They are
  not present in `algorithm/planning/CMakeLists.txt`.
- DLP-specific output/debug payloads are not added to the Normal DDP output
  contract; the remaining DDP debug hook is shared Normal instrumentation.

## Preserved intentionally

- DP initializer code remains buildable.
- Interactive A* remains in the initializer closure.
- DDP and the post-optimization trajectory validator remain in the closure.
- Normal fallback and emergency-stop/AEB behavior remain; these are safety
  fallback behavior, not DLP.
- Strings containing `dlp` in third-party Boost or legacy LongSafe generated
  code are outside the Planning target and are not DLP Planning runtime logic.

## Evidence

- `rg -ni 'dlp|is_dlp|dlp_pp|hold_pp' algorithm/planning/path_planner/src`
  has no DLP runtime references after the removal pass.
- `tap_planning_core` builds in the `thor_x86` container.
- The standalone x86 validation target links against the Thor x86_64 Abseil
  package (not the checked-in AArch64 archive) and passes CTest:
  `tap_planning_validation_smoke` — 100% tests passed.
- The source list is explicit and does not include any DLP-only path.
- The official `cd tap/node && make tgz` Release build explicitly enables the
  Planning core and packages `libtap_planning_core.a` plus its public headers.
- Runtime Node-to-core invocation is intentionally not claimed by this audit;
  it remains part of the later `tap_adapter` integration iteration.

## Non-goals

This audit does not delete unrelated pedal-position fields, generated AEB
code, historical data, or repository history merely because an identifier
contains the letters `dlp`. Those items are not consumed by TAP Planning.
