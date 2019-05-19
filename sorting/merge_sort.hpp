#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace merge_sort {
// sorts iterable and returns true if wasn't timed out
template <typename RandomAccessIterator>
bool sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {})
{
    const size_t arraySize = last - first;
    if (arraySize < 2) {
        return true;
    }

    std::vector<typename RandomAccessIterator::value_type> buffer(first, last);

    for (size_t subarraySize = 2; subarraySize / 2 < arraySize; subarraySize *= 2) {
        if (timeoutPredicate && timeoutPredicate()) {
            return true;
        }
        RandomAccessIterator bufferIt = buffer.begin();
        const size_t numberOfSubarrays = arraySize / subarraySize + (arraySize % subarraySize != 0 ? 1 : 0);

        for (size_t subarrayIndex = 0; subarrayIndex < numberOfSubarrays; ++subarrayIndex) {
            RandomAccessIterator firstSubarrayIndex = first + (subarraySize * subarrayIndex);
            RandomAccessIterator firstSubarrayEnd = firstSubarrayIndex + subarraySize / 2;
            if (firstSubarrayEnd > last) {
                firstSubarrayEnd = last;
            }
            RandomAccessIterator secondSubarrayIndex = firstSubarrayEnd;
            RandomAccessIterator secondSubarrayEnd = secondSubarrayIndex + subarraySize / 2;
            if (secondSubarrayEnd > last) {
                secondSubarrayEnd = last;
            }

            while (true) {
                if (firstSubarrayIndex == firstSubarrayEnd) {
                    bufferIt = std::copy(secondSubarrayIndex, secondSubarrayEnd, bufferIt);
                    break;
                } else if (secondSubarrayIndex == secondSubarrayEnd) {
                    bufferIt = std::copy(firstSubarrayIndex, firstSubarrayEnd, bufferIt);
                    break;
                }

                bool isInOrder = ascendingOrder
                    ? *firstSubarrayIndex <= *secondSubarrayIndex
                    : *firstSubarrayIndex >= *secondSubarrayIndex;

                if (isInOrder) {
                    *bufferIt = *firstSubarrayIndex;
                    ++firstSubarrayIndex;
                } else {
                    *bufferIt = *secondSubarrayIndex;
                    ++secondSubarrayIndex;
                }
                ++bufferIt;
            }
        }

        // TODO: optimize by swapping arrays
        std::copy(buffer.begin(), buffer.end(), first);
    }

    return true;
}
}
