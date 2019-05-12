#pragma once

#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& obj)
{
    stream << "[";
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        stream << *it;
        if (it + 1 != obj.end()) {
            stream << ", ";
        }
    }
    return stream << "]";
}
