#pragma once

#include <algorithm>
#include <iostream>

namespace insertion_sort {
template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last, bool ascendingOrder = true)
{
    if (first == last) {
        return;
    }

    RandomAccessIterator prev = first;
    RandomAccessIterator curr = first;
    ++curr;
    while (curr != last) {
        bool isInOrder = ascendingOrder ? *prev <= *curr : *prev >= *curr;
        if (!isInOrder) {
            // save iterator position to not do extra iterations when we go back
            RandomAccessIterator newPrevIt = prev;
            RandomAccessIterator newCurrIt = curr;
            while (newCurrIt != first) {
                isInOrder = ascendingOrder ? *newPrevIt <= *newCurrIt : *newPrevIt >= *newCurrIt;
                if (isInOrder) {
                    break;
                }
                std::swap(*newPrevIt, *newCurrIt);
                --newPrevIt;
                --newCurrIt;
            }
        }
        ++curr;
        ++prev;
    }
}
}
