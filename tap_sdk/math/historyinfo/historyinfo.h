/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <algorithm>
#include <deque>
namespace active_safety {
namespace math {

template <typename T>
class AsHistoryInfo {
 private:
  std::deque<T> history;
  std::size_t maxSize = 25;

 public:
  explicit AsHistoryInfo(std::size_t maxSize = 25) : maxSize(maxSize) { }

  void push(T x) {
    if (history.size() >= maxSize) {
      history.pop_front();
    }
    history.emplace_back(x);
  }
  T get_frame(std::size_t last_num) const {
    if (history.empty()) {
      return T{};
    }
    if (last_num + 1 > history.size()) {
      return history.back();
    }
    return *(history.rbegin() + last_num);
  }
  void modify_frame(std::size_t index, T newValue) {
    if (index < 0 || index >= history.size()) {
      return;
    }
    *(history.rbegin() + index) = newValue;
  }
  void clear() { history.clear(); }
  void set_size(int sz) {
    maxSize = sz;
    // 如果当前历史数据超过新的maxSize，需要删除多余的数据
    while (history.size() > maxSize) {
      history.pop_front();
    }
  }
  std::size_t size() const { return history.size(); }
  std::size_t capacity() const { return maxSize; }
  void copy_to_array(T *arr, std::size_t size) const {
    if (history.empty()) {
      return;
    }
    const std::size_t availableFrames = history.size();
    if (size > availableFrames) {
      size = availableFrames;
    }
    auto it = history.rbegin();
    for (std::size_t i = 0; i < size; ++i) {
      arr[i] = *it++;
    }
  }
};
}  // namespace math
}  // namespace active_safety
