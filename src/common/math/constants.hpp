#pragma once

#include "prelude.hpp"

namespace math {

namespace {
// clang-format off
constexpr f64 Pi        = 3.141592653589793115997963468544185161590576171875;
constexpr f64 PiHalf    = 1.57079632679489655799898173427209258079528808593755;
constexpr f64 PiQuarter = 0.78539816339744827899949086713604629039764404296875;
constexpr f64 PiInv     = 0.318309886183790691216444201927515678107738494873046875;
constexpr f64 Tau       = 6.28318530717958623199592693708837032318115234375;
constexpr f64 TauInv    = 0.1591549430918953456082221009637578390538692474365234375;
constexpr f64 E         = 2.718281828459045090795598298427648842334747314453125;
// clang-format on
}

/// @brief Mathematical constant Pi.
template <std::floating_point T>
constexpr inline T pi() {
    return T(Pi);
}

/// @brief Mathematical constant Pi / 2.
template <std::floating_point T>
constexpr inline T half_pi() {
    return T(PiHalf);
}

/// @brief Mathematical constant Pi / 4.
template <std::floating_point T>
constexpr inline T quarter_pi() {
    return T(PiQuarter);
}

/// @brief Mathematical constant 1 / Pi.
template <std::floating_point T>
constexpr inline T inv_pi() {
    return T(PiInv);
}

/// @brief Mathematical constant Tau (equal to 2 * Pi).
template <std::floating_point T>
constexpr inline T tau() {
    return T(Tau);
}

/// @brief Mathematical constant 1 / Tau (equal to 1 / (2 * Pi)).
template <std::floating_point T>
constexpr inline T inv_tau() {
    return T(TauInv);
}

/// @brief Mathematical constant e.
template <std::floating_point T>
constexpr inline T e() {
    return T(E);
}

/// @brief Infinity.
template <std::floating_point T>
constexpr inline T infinity() {
    return std::numeric_limits<T>::infinity();
}

}
