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

    /*
    std::cout << std::endl
              << "buffer: ";
    for (const auto& item : buffer) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    */

    for (size_t subarraySize = 2; subarraySize / 2 < arraySize; subarraySize *= 2) {
        // std::cout << "subarraySize = " << subarraySize << std::endl;
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
            /*
            std::cout << "[" << *firstSubarrayIndex << ", " << *firstSubarrayEnd << ")"
                      << "[" << *secondSubarrayIndex << ", " << *secondSubarrayEnd << ")"
                      << std::endl;
                      */

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
                /*
                std::cout << "buffer: ";
                for (const auto& item : buffer) {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
                */
            }
        }
        /*
        std::cout << "done with fucking subarrays " << std::endl;
        */

        // TODO: optimize by swapping arrays
        std::copy(buffer.begin(), buffer.end(), first);

        /*
        std::cout << std::endl
                  << "buffer: ";
        for (const auto& item : buffer) {
            std::cout << item << " ";
        }
        std::cout << std::endl;

        std::cout << std::endl
                  << "original array: ";
        for (auto it = first; it != last; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        */
    }
}
}
