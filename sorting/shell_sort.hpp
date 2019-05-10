#pragma once

#include <algorithm>
#include <iostream>

namespace shell_sort {
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, bool ascendingOrder = true)
{
    for (size_t gap : { 701, 301, 132, 57, 23, 10, 4, 1 }) {
        auto prev = first;
        auto curr = first + gap;

        while (curr < last) {
            bool isInOrder = ascendingOrder ? *prev <= *curr : *prev >= *curr;
            if (!isInOrder) {
                auto newPrev = prev;
                auto newCurr = curr;
                // go back and sort items
                while (newPrev >= first && !isInOrder) {
                    std::swap(*newPrev, *newCurr);
                    newPrev -= gap;
                    newCurr -= gap;
                    isInOrder = ascendingOrder ? *newPrev <= *newCurr : *newPrev >= *newCurr;
                }
            }
            prev += gap;
            curr += gap;
        }
    }
}
}
