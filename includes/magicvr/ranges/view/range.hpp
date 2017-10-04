#ifndef MAGICVR_IRANGE_HPP
#define MAGICVR_IRANGE_HPP

#include <cmath>
#include <cstddef>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

namespace magicvr { namespace ranges { namespace view {

    /**
     * Range that iterates from one value to another using a specific step size.
     *
     * @tparam Value The type of the values to iterate.
     * @param from Start value (inclusive).
     * @param to End value (exclusive).
     * @param stepSize The increment value.
     * @return Range of values.
     */
    template <class Value>
    auto range(Value from, Value to, Value stepSize) {
        const auto size = (std::size_t) std::floor((to - from) / stepSize);
        return ::ranges::view::iota(0, size + 1) |
               ::ranges::view::transform([=](std::size_t i) {
                   return from + i * stepSize;
               });
    }

}}}

#endif //MAGICVR_IRANGE_HPP
