#pragma once
#include <cmath>
#include <iostream>
#include <vector>
namespace active_safety {
namespace math {

class BoolBitwiseProcessor {
 public:
  // 按位与操作（每位对应不同的权重）
  template <typename... Args>
  uint32_t BitWiseAnd(Args... args) {
    clear();
    bool dummy[] = {(values.push_back(args), false)...};
    (void)dummy;

    uint32_t result = 0;
    for (size_t i = 0; i < values.size(); ++i) {
      if (values[i]) {
        result |= (1 << i);
      }
    }
    return result;
  }

  template <typename... Args>
  uint32_t BitWiseOr(Args... args) {
    clear();
    bool dummy[] = {(values.push_back(args), false)...};
    (void)dummy;

    uint32_t result = 0;
    for (size_t i = 0; i < values.size(); ++i) {
      if (values[i]) {
        result |= (1 << i);
      }
    }
    return result;
  }

 private:
  std::vector<bool> values;
  void clear() { values.clear(); }
};

}  // namespace math
}  // namespace active_safety