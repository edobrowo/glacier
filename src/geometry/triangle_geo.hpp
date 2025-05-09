#pragma once

#include "geometry.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Triangle geometry.
class TriangleGeo : public Geometry {
public:
    TriangleGeo();
    TriangleGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~TriangleGeo() = default;

    virtual PrimitivePtr primitive(const Primitive::Kind kind) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    /// @brief Convert the sphere to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;
};
