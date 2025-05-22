#pragma once

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Cuboid geometry.
class Cuboid : public Geometry {
public:
    Cuboid();
    Cuboid(
        const Point3D& Q,
        const Vector3D& x,
        const Vector3D& y,
        const Vector3D& z
    );
    ~Cuboid() override = default;

    TriangleMesh mesh() const override;

    Point3D Q;
    Vector3D x, y, z;
};
