#pragma once

#include "vector_print.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace quick_sort {
template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, bool> partition(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder,
    std::function<bool()> timeoutPredicate);
template <typename RandomAccessIterator>
bool _sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {});

// sorts iterable and returns true if wasn't timed out
template <typename RandomAccessIterator>
bool sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder = true,
    std::function<bool()> timeoutPredicate = {})
{
    std::random_shuffle(first, last);

    return _sort(first, last - 1, ascendingOrder, timeoutPredicate);
}

template <typename RandomAccessIterator>
bool _sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    bool ascendingOrder,
    std::function<bool()> timeoutPredicate)
{
    auto size = last - first;
    if (size < 1) {
        return true;
    }

    auto [pivot, succeded] = partition(first, last, ascendingOrder, timeoutPredicate);
    if (!succeded) {
        return false;
    }
    if (!_sort(first, pivot)) {
        return false;
    }

    if (!_sort(pivot + 1, last)) {
        return false;
    }
    return true;
}

template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, bool> partition(
    RandomAccessIterator _first,
    RandomAccessIterator _last,
    bool ascendingOrder,
    std::function<bool()> timeoutPredicate)
{
    RandomAccessIterator first = _first;
    RandomAccessIterator last = _last;
    int size = last - first;
    if (size < 1) {
        // if one or less elements
        return { last, true };
    }

    auto pivot = *(first + size / 2);
    --first;
    ++last;

    while (true) {
        if (timeoutPredicate && timeoutPredicate()) {
            return { last, false };
        }
        do {
            ++first;
            if (first == _last) {
                break;
            }
        } while (ascendingOrder ? (*first < pivot) : (*first > pivot));

        do {
            --last;
            if (last == _first) {
                break;
            }
        } while (ascendingOrder ? (*last > pivot) : (*last < pivot));

        if (first >= last) {
            break;
        }

        std::swap(*first, *last);
    }

    return { last, true };
}
}
