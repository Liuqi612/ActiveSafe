
#pragma once

#include "pncx_perception.pb.h"
#include <absl/status/status.h>

namespace pnc_x {
namespace prediction {

absl::Status AlignPerceptionObjectTime(double current_time,
                                       ObjectProto *object);

}
}  // namespace pnc_x
