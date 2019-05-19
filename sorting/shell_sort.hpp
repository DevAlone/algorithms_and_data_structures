#pragma once

#include <algorithm>
#include <functional>
#include <iostream>

namespace shell_sort {
// sorts iterable and returns true if wasn't timed out
template <typename RandomAccessIterator>
bool sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {})
{
    for (size_t gap : { 701, 301, 132, 57, 23, 10, 4, 1 }) {
        if (timeoutPredicate && timeoutPredicate()) {
            return false;
        }
        auto prev = first;
        auto curr = first + gap;

        while (curr < last) {
            if (timeoutPredicate && timeoutPredicate()) {
                return false;
            }
            bool isInOrder = ascendingOrder ? *prev <= *curr : *prev >= *curr;
            if (!isInOrder) {
                auto newPrev = prev;
                auto newCurr = curr;
                // go back and sort items
                while (newPrev >= first && !isInOrder) {
                    std::swap(*newPrev, *newCurr);
                    newPrev -= gap;
                    newCurr -= gap;
                    if (newPrev < first) {
                        break;
                    }
                    isInOrder = ascendingOrder ? *newPrev <= *newCurr : *newPrev >= *newCurr;
                }
            }
            prev += gap;
            curr += gap;
        }
    }

    return true;
}
}
