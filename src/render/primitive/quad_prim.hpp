#pragma once

#include "common/math/point.hpp"
#include "common/math/vector.hpp"
#include "primitive.hpp"

/// @brief Quad (bounded plane) 2D primitive.
class QuadPrim : public Primitive {
public:
    QuadPrim(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~QuadPrim() override = default;

    /// @brief Computes the surface intersection with a quadrilateral
    /// represented by barycentric coordinates.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Vector3D mNormal, mW;
    f64 mD;
};
