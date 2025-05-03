#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "primitive.hpp"

/// @brief Disk primitive.
class Disk : public Primitive {
public:
    Disk(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    virtual ~Disk();

    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Vector3D mNormal, mW;
    f64 mD;
};
