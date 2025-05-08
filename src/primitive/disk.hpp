#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "primitive.hpp"

/// @brief Disk primitive.
class Disk : public Primitive {
public:
    Disk();
    Disk(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~Disk() override = default;

    /// @brief Computes the surface intersection with a disk represented by
    /// barycentric coordinates.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Vector3D mNormal, mW;
    f64 mD;
};
