/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <array>
#include <cmath>
#include <stdexcept>
namespace active_safety {
namespace math {

class LookUpTable {
public:
  // 一维线性插值
  static float LinearInterpolation(float x, float x0, float y0, float x1,
                                   float y1);

  // 一维查找表
  template <std::size_t N>
  static float LookupTable1D(const std::array<float, N> &inputData,
                             const std::array<float, N> &outputData,
                             float inputValue) {
    if (inputValue <= inputData.front()) {
      return outputData.front();
    }
    if (inputValue >= inputData.back()) {
      return outputData.back();
    }

    auto it = std::lower_bound(inputData.begin(), inputData.end(), inputValue);
    int lowerIndex = static_cast<std::size_t>(it - inputData.begin()) - 1;

    return LinearInterpolation(
        inputValue, inputData[lowerIndex], outputData[lowerIndex],
        inputData[lowerIndex + 1], outputData[lowerIndex + 1]);
  }

  // 二维查找表
  template <std::size_t N, std::size_t M>
  static float
  LookupTable2D(const std::array<float, N> &x_values,
                const std::array<float, M> &y_values,
                const std::array<std::array<float, M>, N> &lookupTable, float x,
                float y) {
    int x_index = FindIndex<N>(x_values, x);
    int y_index = FindIndex<M>(y_values, y);

    if (x_index == -1 || y_index == -1) {
      throw std::out_of_range("x或y超出范围");
    }

    if (x_index < static_cast<int>(x_values.size() - 1) &&
        y_index < static_cast<int>(y_values.size() - 1)) {
      return Interpolate<N, M>(x_values, y_values, lookupTable, x, y, x_index,
                               y_index);
    }

    return lookupTable[x_index][y_index];
  }

private:
  // 查找索引
  template <std::size_t N>
  static int FindIndex(const std::array<float, N> &values, float value) {
    auto it = std::lower_bound(values.begin(), values.end(), value);

    if (it == values.end()) {
      return values.size() - 1;
    } else if (it == values.begin()) {
      return 0;
    }

    int index = std::distance(values.begin(), it);

    if (it != values.end() &&
        std::abs(values[index] - value) > std::abs(values[index - 1] - value)) {
      --index;
    }

    return index;
  }

  // 二维插值
  template <std::size_t N, std::size_t M>
  static float
  Interpolate(const std::array<float, N> &x_values,
              const std::array<float, M> &y_values,
              const std::array<std::array<float, M>, N> &lookupTable, float x,
              float y, int x_index, int y_index) {
    float x1 = x_values[x_index];
    float x2 = x_values[x_index + 1];
    float y1 = y_values[y_index];
    float y2 = y_values[y_index + 1];

    float Q11 = lookupTable[x_index][y_index];
    float Q12 = lookupTable[x_index][y_index + 1];
    float Q21 = lookupTable[x_index + 1][y_index];
    float Q22 = lookupTable[x_index + 1][y_index + 1];

    return (Q11 * (x2 - x) * (y2 - y) + Q21 * (x - x1) * (y2 - y) +
            Q12 * (x2 - x) * (y - y1) + Q22 * (x - x1) * (y - y1)) /
           ((x2 - x1) * (y2 - y1));
  }
};
} // namespace math
} // namespace active_safety
