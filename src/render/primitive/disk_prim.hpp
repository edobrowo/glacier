#pragma once

#include "common/math/point.hpp"
#include "common/math/vector.hpp"
#include "primitive.hpp"

/// @brief Disk primitive.
class DiskPrim : public Primitive {
public:
    DiskPrim(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~DiskPrim() override = default;

    /// @brief Computes the surface intersection with a disk represented by
    /// barycentric coordinates.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Normal3D mNormal;
    Vector3D mW;
    f64 mD;
};
