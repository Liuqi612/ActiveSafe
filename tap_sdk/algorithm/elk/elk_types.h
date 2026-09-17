#ifndef TAP_SDK_ALGORITHM_ELK_ELK_TYPES_H_
#define TAP_SDK_ALGORITHM_ELK_ELK_TYPES_H_
#include <cstdint>

namespace active_safety {
namespace elk {

enum class ElkLane : uint8_t { CENTER = 0, LEFT = 1, RIGHT = 2 };

enum class CollisionProbability : uint8_t { NONE = 0, LOW = 1, MED = 2, HIGH = 3 };

enum class Confidence : uint8_t { LOW = 0, MED = 1, HIGH = 2 };

enum class DistMode : uint8_t { NONE = 0, YAW_ONLY = 1, VISION_LM = 2, VISION_LM_PROJ = 3 };

enum class ElkState { OFF, FAULT, INHIBIT, STANDBY, ACTIVE };

} // namespace elk
} // namespace active_safety
#endif // TAP_SDK_ALGORITHM_ELK_ELK_TYPES_H_
