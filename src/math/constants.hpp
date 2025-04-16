#pragma once

#include "util/common.hpp"

namespace math {

/// @brief Mathematical constant Pi.
template <std::floating_point T>
constexpr inline T pi() {
    return T(3.141592653589793115997963468544185161590576171875);
}

/// @brief Mathematical constant Pi / 2.
template <std::floating_point T>
constexpr inline T half_pi() {
    return T(1.57079632679489655799898173427209258079528808593755);
}

/// @brief Mathematical constant Pi / 4.
template <std::floating_point T>
constexpr inline T quarter_pi() {
    return T(0.78539816339744827899949086713604629039764404296875);
}

/// @brief Mathematical constant 1 / Pi.
template <std::floating_point T>
constexpr inline T inv_pi() {
    return T(0.318309886183790691216444201927515678107738494873046875);
}

/// @brief Mathematical constant Tau (2 * Pi).
template <std::floating_point T>
constexpr inline T tau() {
    return T(6.28318530717958623199592693708837032318115234375);
}

/// @brief Mathematical constant 1 / Tau (1 / (2 * Pi)).
template <std::floating_point T>
constexpr inline T inv_tau() {
    return T(0.1591549430918953456082221009637578390538692474365234375);
}

/// @brief Mathematical constant e.
template <std::floating_point T>
constexpr inline T e() {
    return T(2.718281828459045090795598298427648842334747314453125);
}

}
