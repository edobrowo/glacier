#pragma once

#include "math/constants.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

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

    /// @brief The unit interval, defined [0, 1].
    static const Interval unit;

    /// @brief Determines the size of the interval.
    f64 size() const;

    /// @brief Determines whether `a` lines within the interval, inclusive.
    bool contains(const f64 a) const;

    /// @brief Determines whether `a` lines within the interval, exclusive.
    bool surrounds(const f64 a) const;

    /// @brief Creates a new interval by padding the current interval with
    /// epsilon / 2. That is, [min - epsilon / 2, max + epsilon / 2].
    Interval expand(const f64 epsilon) const;

    /// @brief Creates a new interval that tightly encloses two intervals.
    Interval enclosure(const Interval& other) const;

    /// @brief Creates a new interval that is the intersection of two intervals.
    Interval intersection(const Interval& other) const;

    f64 min;
    f64 max;
};

template <>
struct FormatWriter<Interval> {
    static void write(const Interval& value, StringBuffer& sb) {
        sb.appendFormat("[{},{}]", value.min, value.max);
    }
};
