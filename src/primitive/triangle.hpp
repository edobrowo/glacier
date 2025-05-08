#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "primitive.hpp"

/// @brief Triangle primitive.
class Triangle : public Primitive {
public:
    Triangle();
    Triangle(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~Triangle() override = default;

    /// @brief Computes the surface intersection with a triangle represented by
    /// barycentric coordinates.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Vector3D mNormal, mW;
    f64 mD;
};
