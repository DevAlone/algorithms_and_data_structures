#pragma once

#include <algorithm>
#include <functional>
#include <iostream>

namespace insertion_sort {
// sorts iterable and returns true if wasn't timed out
template <typename RandomAccessIterator>
bool sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {})
{
    if (first == last) {
        return true;
    }

    RandomAccessIterator prev = first;
    RandomAccessIterator curr = first;
    ++curr;
    while (curr != last) {
        if (timeoutPredicate && timeoutPredicate()) {
            return false;
        }
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

    return true;
}
}
