#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "util/common.hpp"

/// @brief Ray-surface intersection record.
struct Intersect {
    enum class Face {
        Outside = 0,
        Inside
    };

    f64 t;
    Point3D position;
    Vector3D normal;
    Face face;

    Intersect(
        const f64 t,
        const Point3D& position,
        const Vector3D& normal,
        const Face face
    );
    ~Intersect() = default;

    Intersect(const Intersect& other);
    Intersect& operator=(const Intersect& other);

    Intersect(Intersect&& other);
    Intersect& operator=(Intersect&& other);
};
