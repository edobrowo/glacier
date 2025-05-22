#pragma once

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Quad geometry.
class Quad : public Geometry {
public:
    Quad();
    Quad(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~Quad() override = default;

    TriangleMesh mesh() const override;

    Point3D Q;
    Vector3D x, y;
};
