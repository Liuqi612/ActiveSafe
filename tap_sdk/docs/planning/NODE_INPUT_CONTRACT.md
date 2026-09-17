# Planning Node Input Contract (Emergency Planning)

This contract is implemented at the `tap/node -> tap_adapter ->
tap_planning_core` boundary. The TAP node also owns Active Safety; its
Planning callbacks decode Normal RSCL payloads, align them by source timestamp,
and construct normalized inputs. The current runtime executes
`Initializer (Interactive A*) -> DDP -> ValidateTrajectory`, converts the
validated result to the standard vehicle-frame trajectory contract, and
publishes it for control/replay/SIL consumption.

## Snapshot rule

Each planning tick creates one coherent snapshot using the planning-frame
timestamp `T`. A message is usable only when its source timestamp is not newer
than `T`, is not older than the age limit below, and passes its message-level
validity checks. Missing mandatory data fails the tick or selects the explicit
Normal fallback; it must not be replaced with invented map, localization, or
object data.

| Internal input | Reference source | Frame / units | Max age | Consumer | Missing action |
| --- | --- | --- | --- | --- | --- |
| `plan_start_point` / ego state | `/localization/odomstate_info` (`OdomStateInfo`) | source frame converted to Planning local frame; m, rad, m/s, m/s², timestamp ns | 100 ms snapshot age; map/prediction pose match ≤50 ms | Initializer, DDP | reject snapshot; no fabricated pose |
| road structure / lane path | `/maplesslm/scene_navi_map` (`SceneNaviMap`) | vehicle or local source frame; converted corridor in local m; map timestamp ns | 500 ms | Drive passage, Interactive A*, DP | reject snapshot; no synthetic lane |
| fused objects and prediction | `/prediction/objects` (`Prediction`) | vehicle or local source frame; converted to local m/rad/m/s and relative seconds | 200 ms objects / 300 ms prediction | object costs/collision checker, spacetime trajectories | reject malformed or unaligned payload; valid explicit empty list is allowed |
| LongSafe AEB threat decision | `LgSafe2024Function::GetSelectOut().longsafe_aeb.{fus_trkId,ttc,status}`, produced from `/perception/fusion/object` | positive `int32_t` fusion track ID, TTC in s, Fusion track lifecycle status, source timestamp ns | target age ≤300 ms and Fusion/Prediction timestamp delta ≤300 ms | first match the Prediction object by ID, then apply the configurable TTC gate (default ≤3 s) | invalid/stale/future decision, unmatched Prediction object, or TTC above threshold rejects/skips the emergency tick; A*/DDP is not run |
| occupancy / dangerous zones | `/perception/nv_cameras/occ_info` (`OccupancyInfo`) | source frame; timestamp ns | 300 ms | reserved optional Normal cost input | record snapshot validity; not consumed by the current native-input gate |
| route guidance / lane info | `rscl/RouteGuidance`, `LaneInfo`, `NaviSegmentList` | map frame; m | 1 s | reference-line search and lane decisions | retain last valid route only within age limit; otherwise Normal fallback |
| traffic rules | `rscl/TrafficLight`, `SpeedLimit` | map frame; m/s | 1 s | speed limit and decision costs | use conservative valid default only where the protobuf contract defines one |
| prior validated trajectory / longitudinal acceleration | `/decision_planning/trajectory` (`Trajectory`) | `vehicle` frame; header publish timestamp ns; point timestamp ns; x forward / y left in m; acceleration m/s² | acceleration point must be at or before header time and no older than 30 ms | LongSafe previous longitudinal-control input; DDP warm start remains runtime-owned | use zero longitudinal deceleration when no point matches; do not block the Planning tick |

## Adapter responsibilities

The Node owns subscription and timestamped payload history. `planning_snapshot_`
selects samples at or before the planning-frame timestamp `T`; ego history is
kept at 128 samples and road/prediction histories at 16 samples. Vehicle-frame
road/prediction payloads require the newest localization sample not newer than
the payload and within 50 ms. Local-frame map payloads do not need a second
pose. No pose extrapolation or newest-of-each-topic mixing is performed.

`planning_rscl_converter.cc` owns Cap'n Proto decoding, vehicle-to-local rigid
transforms, lane/lane-link corridor construction, routing-successor ambiguity
rejection, and prediction kinematics. Negative Prediction IDs are excluded so
DLP-only records cannot enter Emergency Planning. LongSafe contributes only its
positive fusion track ID; the converter matches that ID in the decoded integer
Prediction domain before converting it to Planning's string object ID. No
LongSafe position, contour, speed, acceleration, or predicted path is reused.
The Planning core receives only the lightweight normalized DTOs and has no
RSCL subscriber dependency.

## Normalized geometry contract

`tap_planning_core_adapter` is the boundary between decoded platform messages
and the upstream Planning types. Its public input contains no RSCL or Cap'n
Proto reader:

- `NormalizedEgoState`: local Cartesian x/y in metres, heading in radians,
  speed in m/s, acceleration in m/s², and curvature in 1/m.
- `NormalizedRoadCorridor`: at least two centre points, local `s` starting at
  zero and increasing strictly, lane ID, left/right positive width in metres,
  boundary type, and speed limit in m/s.
- `BuildPlanningGeometry`: atomically creates
  `ApolloTrajectoryPointProto`, `DrivePassage`, and the upstream-built
  `PathSlBoundary`, then verifies that ego projects inside the corridor.
- `BuildSpacetimeTrajectoryManager`: requires each object to have a unique
  non-empty ID, a strict convex contour, one or more valid trajectories, and
  one common source timestamp. Static one-point predictions use the upstream
  stationary-horizon expansion; no object-only prediction is synthesized.

The adapter rejects zero timestamps, NaN/Inf, zero lane IDs, lane sequence
re-entry, duplicate/non-monotonic points, `s`/geometry discontinuity,
non-positive or implausibly large widths, invalid heading/coordinate ranges,
invalid speed limits, and ego outside the corridor. These are observable input
errors; the adapter does not repair them with a synthetic lane or pose.

## Runtime and output contract

The emergency runtime order is strict: map the LongSafe Fusion ID to the
aligned Prediction object collection, retain every Prediction branch belonging
to that object, validate lifecycle/TTC (default `TTC <= 3 s`), run Interactive
A* to obtain the coarse trajectory, pass that exact coarse trajectory to DDP,
and finally run `ValidateTrajectory`. Both the A* and DDP outputs are also
checked against every Prediction branch of the selected target. A failure at
any stage publishes no trajectory. `EMERGENCY_AVOIDANCE` is upstream object
metadata; collision avoidance is provided by the Prediction trajectories in
the normal spacetime obstacle/cost pipeline, not by the enum alone.

The runtime facade returns a trajectory only after the upstream
`ValidateTrajectory` succeeds. `OnPlanningTimer` converts the Planning-local
points into the standard `vehicle` frame (`position.x` longitudinal forward,
`position.y` lateral left), sets `trajTimestampNs=T`, timestamps each point as
`T + relative_time`, and publishes `/decision_planning/trajectory`. Empty,
non-finite, decreasing-time/distance, future-source, and timestamp-overflow
outputs are rejected before publication. The message is `GEAR_DRIVE`,
`MODE_LKA`, `MAPLESS`, and `trajState=1`.

The Node also subscribes to this topic because LongSafe consumes the preceding
trajectory's longitudinal acceleration. That callback only updates the
LongSafe input cache and cannot trigger another planning publication. DDP warm
start state is retained inside `EmergencyPlanningRuntime`; it is not reconstructed
from an arbitrary newest trajectory message. The Node still does not implement
any planning algorithm. Real object predictions are passed to both
`SpacetimeTrajectoryManager` and the Normal
`SpacetimePlannerObjectTrajectories` view consumed by Interactive A*/DDP. Every
object remains in that view. Trajectories belonging to the matched LongSafe ID
use the upstream `EMERGENCY_AVOIDANCE` reason; all other trajectories keep the
Normal `ALL` reason. This Node path is emergency-only: a missing, expired, or
unmatched LongSafe decision blocks that tick instead of publishing an ordinary
trajectory.

SIL strictly accepts non-empty `vehicle`-frame trajectories with finite,
non-decreasing point time/distance and valid source/publish timestamps. Replay
uses the exact trajectory header timestamp when present, otherwise the nearest
preceding frame within 300 ms. BirdView renders the published centerline and a
1.925 m vehicle-width corridor; it no longer depends on the legacy LongSafe ego
path.

## Verification hooks

- Unit tests for stale, future, out-of-order, missing, and frame-mismatch input.
- Real Cap'n Proto Builder/Reader conversion tests for Odom, SceneNaviMap,
  Prediction, local-frame transforms, lane-link routing, and invalid contours.
- Replay test with identical normalized snapshots must produce identical
  intermediate initializer and DDP result within the documented tolerance.
- The current runtime facade smoke covers an empty scene and a moving obstacle;
  the moving obstacle is also matched by a LongSafe-style fusion ID and echoed
  in the validated runtime result.
- The LongSafe bridge smoke loads the production calibration JSON, runs VSE,
  Fusion-object conversion, and `LgSafe2024Function::Update`; it verifies both
  empty-scene no-selection and a straight-driving stationary-car scene that
  selects the real nonzero `fus_trkId=7`.
- The trajectory converter test covers local-to-vehicle transformation,
  direction/heading, timestamps, velocity/acceleration/jerk/yaw-rate, message
  enums, malformed values, future source time, and nanosecond overflow.
- The standalone SIL test covers complete Cap'n Proto parsing, strict frame and
  timestamp rejection, acceleration selection, vehicle-width corridor
  geometry, and NaN rejection. The full `as_sil` target links and remains alive
  in an offscreen five-second startup smoke with project runtime libraries.
- A mandatory-input failure must be observable; it must not silently become a
  fabricated default.
- Straight, curved, lane-transition, malformed-corridor, boundary-generation,
  and ego-outside-corridor tests run with assertions explicitly enabled even
  in Release builds.
- Moving/static object conversion and rejection of invalid contour, trajectory,
  probability, timestamp, unit, and duplicate-ID inputs are covered by the
  object adapter test.
