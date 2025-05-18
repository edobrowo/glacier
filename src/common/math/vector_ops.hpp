#pragma once

#include "math/vector.hpp"
#include "prelude.hpp"

namespace math {

/// @brief Projects vector `v` onto vector `w`.
Vector3D project(const Vector3D& v, const Vector3D& w);

/// @brief Computes the angle between vectors `v` and `w`.
f64 angle(const Vector3D& v, const Vector3D& w);

/// @brief Perturbs vector `v` by spherical coordinates `alpha` and `beta`.
Vector3D perturb(const Vector3D& v, const f64 alpha, const f64 beta);

/// @brief Reflects vector `l` through normal `n`.
Vector3D reflect(const Vector3D& l, const Vector3D& n);

/// @brief Refracts vector `l` via normal `n` via refractive index ratio `eta`.
Vector3D refract(const Vector3D& l, const Vector3D& n, const f64 eta);

};
