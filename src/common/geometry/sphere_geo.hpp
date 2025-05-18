#pragma once

#include "geometry/geometry.hpp"
#include "math/point.hpp"
#include "prelude.hpp"
#include "primitive/primitive.hpp"

/// @brief Sphere geometry.
class SphereGeo : public Geometry {
public:
    SphereGeo();
    SphereGeo(const Point3D& center, const f64 radius);
    ~SphereGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

    /// @brief Retrieve a constant reference to the center.
    const Point3D& center() const;

    /// @brief Retrieve the radius.
    f64 radius() const;

    /// @brief Set number of UV divisions for UV mesh construction
    void setDivisions(const Size u_div, const Size v_div);

private:
    Point3D mCenter;
    f64 mRadius;
    Size mUDiv, mVDiv;

    /// @brief Convert the sphere to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the sphere to a mesh via UV construction.
    PrimitivePtr buildMeshPrimitive() const;
};
