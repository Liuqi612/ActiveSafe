
#pragma once

#include <string>

#include "base/macros.h"
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>

#include "maps/semantic_map_defs.h"

#define SMM_CONCAT3(x, y, z) SMM_CONCAT(x, SMM_CONCAT(y, z))
#define SMM_CONCAT(x, y) SMM_CONCAT_IMPL(x, y)
#define SMM_CONCAT_IMPL(x, y) x##y
