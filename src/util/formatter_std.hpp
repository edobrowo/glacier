#pragma once

#include <array>
#include <cstring>
#include <map>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "formatter.hpp"

template <>
struct FormatWriter<std::string> {
    static void write(const std::string& value, StringBuffer& sb) {
        sb.append(value);
    }
};

template <>
struct FormatWriter<std::string_view> {
    static void write(const std::string_view value, StringBuffer& sb) {
        sb.append(value);
    }
};

template <typename T>
    requires FormatWritable<T>
struct FormatWriter<Option<T>> {
    static void write(const Option<T>& opt, StringBuffer& sb) {
        if (opt) {
            sb.append("Some(", 5);
            FormatWriter<T>::write(*opt, sb);
            sb.putSafe(')');
        } else {
            sb.append("None", 4);
        }
    }
};

template <typename T, typename U>
    requires FormatWritable<T> && FormatWritable<U>
struct FormatWriter<std::pair<T, U>> {
    static void write(const std::pair<T, U>& pair, StringBuffer& sb) {
        sb.putSafe('(');
        FormatWriter<T>::write(pair.first, sb);
        sb.putSafe(',');
        FormatWriter<U>::write(pair.second, sb);
        sb.putSafe(')');
    }
};

template <typename T, std::size_t N>
    requires FormatWritable<T> && FormatWritable<std::size_t>
struct FormatWriter<std::array<T, N>> {
    static void write(const std::array<T, N>& arr, StringBuffer& sb) {
        sb.putSafe('[');
        for (auto iter = arr.begin(); iter != arr.end(); ++iter) {
            FormatWriter<T>::write(*iter, sb);
            if (distance(iter, arr.end()) > 1)
                sb.putSafe(',');
        }
        sb.putSafe(']');
    }
};

template <typename T>
    requires FormatWritable<T>
struct FormatWriter<std::vector<T>> {
    static void write(const std::vector<T>& vec, StringBuffer& sb) {
        sb.putSafe('[');
        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
            FormatWriter<T>::write(*iter, sb);
            if (distance(iter, vec.end()) > 1)
                sb.putSafe(',');
        }
        sb.putSafe(']');
    }
};

template <typename T>
    requires FormatWritable<T>
struct FormatWriter<std::span<T>> {
    static void write(const std::span<T>& span, StringBuffer& sb) {
        sb.putSafe('[');
        for (auto iter = span.begin(); iter != span.end(); ++iter) {
            FormatWriter<T>::write(*iter, sb);
            if (distance(iter, span.end()) > 1)
                sb.putSafe(',');
        }
        sb.putSafe(']');
    }
};

template <typename K, typename V>
    requires FormatWritable<K> && FormatWritable<V>
struct FormatWriter<std::map<K, V>> {
    static void write(const std::map<K, V>& hashmap, StringBuffer& sb) {
        sb.putSafe('{');
        for (auto iter = hashmap.begin(); iter != hashmap.end(); ++iter) {
            sb.putSafe('{');
            FormatWriter<K>::write(iter->first, sb);
            sb.putSafe(',');
            FormatWriter<V>::write(iter->second, sb);
            sb.putSafe('}');
            if (distance(iter, hashmap.end()) > 1)
                sb.append(", ", 2);
        }
        sb.putSafe('}');
    }
};
