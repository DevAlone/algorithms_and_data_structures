#pragma once

#include <algorithm>

namespace selection_sort {
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, bool ascendingOrder = true)
{
    while (first != last) {
        if (ascendingOrder) {
            auto smallestIt = std::min_element(first, last);
            std::swap(*first, *smallestIt);

        } else {
            auto greatestIt = std::max_element(first, last);
            std::swap(*first, *greatestIt);
        }
        ++first;
    }
}
}
