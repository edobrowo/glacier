#pragma once

#include "constants.hpp"
#include "util/common.hpp"

/// @brief Real number interval.
class Interval {
public:
    Interval(const f64 min, const f64 max);
    ~Interval() = default;

    Interval(const Interval& other);
    Interval& operator=(const Interval& other);

    /// @brief The empty interval, defined [infty, -infty].
    static const Interval empty;

    /// @brief The universe interval, defined [-infty, infty].
    static const Interval universe;

    /// @brief Determines whether `a` lines within the interval, inclusive.
    bool contains(const f64 a) const;

    /// @brief Determines whether `a` lines within the interval, exclusive.
    bool surrounds(const f64 a) const;

    f64 min;
    f64 max;
};
