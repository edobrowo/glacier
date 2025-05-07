#pragma once

#include <string_view>

#include "common.hpp"

// TODO: Wide characters.
class StringBuffer {
public:
    StringBuffer();
    ~StringBuffer();

    const char* str();
    std::string toString();

    Size length();
    bool isEmpty();

    void put(const char c);
    void putSafe(const char c);

    void append(const char* str, const Size length);
    void append(const std::string& str);
    void append(const std::string_view view);

    template <typename... Targs>
    void appendFormat(const char* format_string, Targs... args) {
        format(*this, format_string, args...);
    }

private:
    void expand(const Size size);

    Size mCapacity;
    Index mNext;
    char* mBuffer;

    static constexpr Size INITIAL_CAPACITY = 200;
    static constexpr Size CAPACITY_INCREMENT = 200;
};
