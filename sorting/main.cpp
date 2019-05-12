#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "selection_sort.hpp"
#include "shell_sort.hpp"
#include "vector_print.h"

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <set>
#include <string>
#include <thread>
#include <vector>

/* const std::vector<size_t> RANDOM_BENCH_SIZES = {
    8, 128, 1024, 16384, 65536, 131072
}; */
const size_t BENCH_ARRAY_SIZE_LIMITER = 10'000'000;
// each case need to be repeated with random data to measure the average time
const size_t BENCH_NUMBER_OF_REPETITION = 3;
const auto FIELD_WIDTH = 12;
const size_t TIMEOUT_SECONDS = 10;

template <typename RandomAccessIterator>
bool isDataSorted(RandomAccessIterator it, RandomAccessIterator last, bool ascendingOrder = true)
{
    RandomAccessIterator prev = it;
    ++it;
    while (it != last) {
        if (ascendingOrder) {
            if (*prev > *it) {
                return false;
            }
        } else {
            if (*prev < *it) {
                return false;
            }
        }
        ++it;
    }
    return true;
}

template <typename RandomAccessIterator>
double _benchmarkSortingAlgorithmWithData(
    std::function<void(RandomAccessIterator, RandomAccessIterator)> sort,
    std::vector<typename RandomAccessIterator::value_type> data)
{
    using clock = std::chrono::steady_clock;

    std::set<typename RandomAccessIterator::value_type> itemsBeforeOrdering(data.begin(), data.end());

    auto startTime = clock::now();
    sort(data.begin(), data.end());
    auto endTime = clock::now();

    std::set<typename RandomAccessIterator::value_type> itemsAfterOrdering(data.begin(), data.end());

    if (itemsAfterOrdering.size() != itemsBeforeOrdering.size()) {
        throw std::logic_error("Array items set was changed during sorting");
    }

    for (auto item : itemsAfterOrdering) {
        auto it = itemsBeforeOrdering.find(item);
        if (it == itemsBeforeOrdering.end()) {
            std::cout << "Item "
                      << item
                      << "was not in the array before sorting";
            throw std::logic_error("wrong items");
        }
    }

    if (!isDataSorted(data.begin(), data.end())) {
        std::cout << "wrong order. First 50 elements are: ";
        auto it = data.begin();
        for (size_t i = 0; i < 50 && it != data.end(); ++i) {
            std::cout << *it << " ";
            ++it;
        }
        std::cout << std::endl;
        throw std::logic_error("wrong order");
    }
    auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    return double(timeElapsed) / 1000000.0;
}

template <typename RandomAccessIterator>
std::pair<double, bool> benchmarkSortingAlgorithmWithData(
    std::function<void(RandomAccessIterator, RandomAccessIterator)> sort,
    const std::vector<typename RandomAccessIterator::value_type>& data)
{
    using namespace std::chrono_literals;
    // call
    std::mutex m;
    std::condition_variable cv;
    double result;

    pthread_t nativeHandle;
    {
        std::thread t([&cv, &result, &sort, &data]() {
            result = _benchmarkSortingAlgorithmWithData<RandomAccessIterator>(sort, data);
            cv.notify_one();
        });
        nativeHandle = t.native_handle();
        t.detach();
    }

    std::unique_lock<std::mutex> l(m);
    if (cv.wait_for(l, 1s * TIMEOUT_SECONDS) == std::cv_status::timeout) {
        pthread_cancel(nativeHandle);
        return { 0, true };
    }

    return { result, false };
}

template <typename RandomAccessIterator>
struct SortingAlgorithm {
    SortingAlgorithm(
        const char* shortName,
        const char* name,
        std::function<void(RandomAccessIterator, RandomAccessIterator)> func)
        : shortName(shortName)
        , name(name)
        , func(func)
    {
    }
    std::string shortName;
    std::string name;
    std::function<void(RandomAccessIterator, RandomAccessIterator)> func;
};

int main()
{
    srand(time(0));
    using IteratorType = std::vector<int>::iterator;

    std::vector<SortingAlgorithm<IteratorType>> algorithms {
        SortingAlgorithm<IteratorType>(
            "BS", "bubble sort",
            [](IteratorType first, IteratorType last) {
                bubble_sort::sort(first, last, true);
            }),
        SortingAlgorithm<IteratorType>(
            "SS", "selection sort",
            [](IteratorType first, IteratorType last) {
                selection_sort::sort(first, last, true);
            }),
        SortingAlgorithm<IteratorType>(
            "IS", "insertion sort",
            [](IteratorType first, IteratorType last) {
                insertion_sort::sort(first, last, true);
            }),
        SortingAlgorithm<IteratorType>(
            "SHS", "shell sort",
            [](IteratorType first, IteratorType last) {
                shell_sort::sort(first, last, true);
            }),
        SortingAlgorithm<IteratorType>(
            "MS", "merge sort",
            [](IteratorType first, IteratorType last) {
                merge_sort::sort(first, last, true);
            }),
    };

    // test
    for (const auto& sortingAlgorithm : algorithms) {
        auto testCases = std::vector<std::vector<int>> {
            { -1, 5, 10, 19, 8, 9 },
            { 1, 1, 1 },
            { 9, 2, 7 },
            { 9, 2, -10 },
            { -15, 10, 100, 200 },
            { 1 },
            { 1, 2 },
            { 2, 1 },
            {},
        };
        for (const auto& data : testCases) {
            auto correntSortedData = data;
            std::sort(correntSortedData.begin(), correntSortedData.end());
            auto sortedDataByAlgorithm = data;
            sortingAlgorithm.func(sortedDataByAlgorithm.begin(), sortedDataByAlgorithm.end());
            if (correntSortedData != sortedDataByAlgorithm) {
                std::cout << "wrong answer. \nExpected: \t";
                for (const auto& item : correntSortedData) {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
                std::cout << "Actual: \t";
                for (const auto& item : sortedDataByAlgorithm) {
                    std::cout << item << " ";
                }
                std::cout << std::endl;
                throw std::logic_error(std::string("algorithm ") + sortingAlgorithm.name + " gave wrong answer");
            }
        }
    }

    // benchmark

    for (const auto& sortingAlgorithm : algorithms) {
        std::cout << sortingAlgorithm.shortName << " - " << sortingAlgorithm.name << std::endl;
    }

    std::cout
        << std::setw(FIELD_WIDTH) << " "
        << ":";
    for (const auto& sortingAlgorithm : algorithms) {
        std::cout << std::setw(FIELD_WIDTH) << std::right << sortingAlgorithm.shortName << "|";
    }
    std::cout << std::endl;

    for (size_t n = 0; n < BENCH_ARRAY_SIZE_LIMITER; ++n) {
        bool atLeastOneAlgorithmSucced = false;
        size_t size = std::pow(2, n);
        std::cout << std::setw(FIELD_WIDTH) << size << ":";
        std::cout.flush();

        for (const auto& algorithm : algorithms) {
            double result = 0;
            bool hasTimedout = false;
            for (size_t k = 0; k < BENCH_NUMBER_OF_REPETITION; ++k) {
                // generate the data
                if (size >= BENCH_ARRAY_SIZE_LIMITER) {
                    return 0;
                }
                std::vector<int> testData1;
                for (size_t i = 0; i < size; ++i) {
                    testData1.push_back(rand() % 100);
                }
                // sort it

                auto res = benchmarkSortingAlgorithmWithData<IteratorType>(
                    algorithm.func,
                    testData1);
                result += res.first;
                hasTimedout |= res.second;
                if (hasTimedout) {
                    break;
                }
            }
            atLeastOneAlgorithmSucced |= not hasTimedout;
            // print result
            result /= double(BENCH_NUMBER_OF_REPETITION);
            std::cout
                << std::fixed
                << std::setprecision(FIELD_WIDTH)
                << std::setw(FIELD_WIDTH)
                << (hasTimedout ? "timeout" : std::to_string(result))
                << "|";
            std::cout.flush();
        }
        if (!atLeastOneAlgorithmSucced) {
            return 0;
        }

        std::cout << std::endl;
    }

    return 0;
}
