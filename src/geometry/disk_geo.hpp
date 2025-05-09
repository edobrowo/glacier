#pragma once

#include "geometry.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Disk geometry.
class DiskGeo : public Geometry {
public:
    DiskGeo();
    DiskGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~DiskGeo() = default;

    virtual PrimitivePtr primitive(const Primitive::Kind kind) const override;

private:
    Point3D mQ;
    Vector3D mU, mV;

    /// @brief Convert the disk to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the disk to a mesh representation.
    PrimitivePtr buildMeshPrimitive() const;
};
