#pragma once

#include "geometry.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Cuboid geometry.
class CuboidGeo : public Geometry {
public:
    CuboidGeo();
    CuboidGeo(
        const Point3D& Q,
        const Vector3D& x,
        const Vector3D& y,
        const Vector3D& z
    );
    ~CuboidGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

private:
    Point3D mQ;
    Vector3D mX, mY, mZ;

    /// @brief Convert the cuboid to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the cuboid to a mesh via UV construction.
    PrimitivePtr buildMeshPrimitive() const;
};
