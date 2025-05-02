#pragma once

#include "math/point.hpp"
#include "math/vector.hpp"
#include "primitive.hpp"

class Quad : public Primitive {
public:
    Quad(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    virtual ~Quad();

    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    Vector3D mNormal, mW;
    f64 mD;
};
