#pragma once

#include "geometry/geometry.hpp"
#include "math/point.hpp"
#include "prelude.hpp"
#include "primitive/primitive.hpp"

/// @brief Quad geometry.
class QuadGeo : public Geometry {
public:
    QuadGeo();
    QuadGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~QuadGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    /// @brief Convert the quad to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the quad to a mesh representation.
    PrimitivePtr buildMeshPrimitive() const;
};
