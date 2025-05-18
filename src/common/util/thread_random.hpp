#pragma once

#include <random>

#include "prelude.hpp"

namespace thread_rng {

/// @brief Generate a thread-local uniform random value.
template <std::floating_point T>
inline T uniform() {
    thread_local std::uniform_real_distribution<T> distribution(T(0), T(1));
    thread_local std::mt19937 generator;

    return distribution(generator);
}

/// @brief Generate a thread-local uniform random value along an interval.
template <std::floating_point T>
inline T uniform(const T min, const T max) {
    return min + (max - min) * uniform<T>();
}

};
