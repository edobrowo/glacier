#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "util/common.hpp"

/// @brief Ray-surface intersection record.
struct Intersect {
    f64 t;
    Point3D position;
    Vector3D normal;

    Intersect(const f64 t, const Point3D& position, const Vector3D& normal);
    ~Intersect() = default;

    Intersect(const Intersect& other);
    Intersect& operator=(const Intersect& other);

    Intersect(Intersect&& other);
    Intersect& operator=(Intersect&& other);
};
