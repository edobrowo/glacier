#pragma once

#include "geometry/geometry.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Triangle geometry.
class Triangle : public Geometry {
public:
    Triangle();
    Triangle(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~Triangle() override = default;

    TriangleMesh mesh() const override;

    Point3D Q;
    Vector3D x, y;
};
