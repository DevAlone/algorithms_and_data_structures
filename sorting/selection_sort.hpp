#pragma once

#include <algorithm>
#include <functional>

namespace selection_sort {
// sorts iterable and returns true if wasn't timed out
template <typename RandomAccessIterator>
bool sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {})
{
    while (first != last) {
        if (timeoutPredicate && timeoutPredicate()) {
            return false;
        }
        if (ascendingOrder) {
            auto smallestIt = std::min_element(first, last);
            std::swap(*first, *smallestIt);

        } else {
            auto greatestIt = std::max_element(first, last);
            std::swap(*first, *greatestIt);
        }
        ++first;
    }
    return true;
}
}
