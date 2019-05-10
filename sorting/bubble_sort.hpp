#pragma once

#include <algorithm>
#include <iostream>

namespace bubble_sort {
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, bool ascendingOrder = true)
{
    while (first != last) {
        bool wasSwapped = false;
        auto prev = first;
        auto curr = first;
        ++curr;
        while (curr != last) {
            bool isInOrder = ascendingOrder ? *prev <= *curr : *prev >= *curr;
            if (!isInOrder) {
                std::swap(*prev, *curr);
                wasSwapped = true;
            }
            ++prev;
            ++curr;
        }

        if (!wasSwapped) {
            break;
        }
        --last;
    }
}
}
