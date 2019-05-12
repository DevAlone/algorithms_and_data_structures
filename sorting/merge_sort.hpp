#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

namespace merge_sort {
template <typename RandomAccessIterator>
void sort(const RandomAccessIterator first, const RandomAccessIterator last, const bool ascendingOrder = true)
{
    const size_t arraySize = last - first;
    if (arraySize < 2) {
        return;
    }

    std::vector<typename RandomAccessIterator::value_type> buffer(first, last);

    for (size_t subarraySize = 2; subarraySize / 2 < arraySize; subarraySize *= 2) {
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
}
}
