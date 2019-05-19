#pragma once

#include <algorithm>
#include <functional>
#include <iostream>

namespace bubble_sort {
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
        bool wasSwapped = false;
        auto prev = first;
        auto curr = first;
        ++curr;
        while (curr != last) {
            if (timeoutPredicate && timeoutPredicate()) {
                return false;
            }
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
    return true;
}
}
