#pragma once

#include "matrix.hpp"
#include "point.hpp"
#include "vector.hpp"

/// @brief 3D ray class.
class Ray {
public:
    Ray(const Point3D& origin, const Vector3D& direction);
    ~Ray() = default;

    Point3D at(const f64 t) const;

    Point3D origin;
    Vector3D direction;
};
