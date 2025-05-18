#pragma once

#include "geometry/geometry.hpp"
#include "math/point.hpp"
#include "prelude.hpp"
#include "primitive/primitive.hpp"

/// @brief Disk geometry.
class DiskGeo : public Geometry {
public:
    DiskGeo();
    DiskGeo(const Point3D& Q, const Vector3D& u, const Vector3D& v);
    ~DiskGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

    /// @brief Set number of divisions for UV mesh construction
    void setDivisions(const Size div);

private:
    Point3D mQ;
    Vector3D mU, mV;
    Size mDiv;

    /// @brief Convert the disk to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the disk to a mesh representation.
    PrimitivePtr buildMeshPrimitive() const;
};
