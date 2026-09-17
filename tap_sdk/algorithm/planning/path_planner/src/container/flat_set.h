
#pragma once

#include <functional>

#include <boost/container/flat_set.hpp>

namespace pnc_x {

template <typename T, typename Compare = std::less<T>>
using FlatSet = boost::container::flat_set<T, Compare>;

}
