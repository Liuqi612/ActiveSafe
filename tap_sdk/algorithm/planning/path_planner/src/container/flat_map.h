
#pragma once

#include <functional>

#include <boost/container/flat_map.hpp>

namespace pnc_x {

template <typename K, typename V, typename Compare = std::less<K>>
using FlatMap = boost::container::flat_map<K, V, Compare>;

}
