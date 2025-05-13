#pragma once

#include "geometry.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Tube geometry.
class TubeGeo : public Geometry {
public:
    TubeGeo();
    TubeGeo(const Point3D& center, const f64 radius, const f64 height);
    ~TubeGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

    void setCapVisibility(const bool top, const bool bottom);

    /// @brief Set number of divisions for UV mesh construction
    void setDivisions(const Size div);

private:
    Point3D mCenter;
    f64 mRadius, mHeight;
    bool mTopCap, mBottomCap;
    Size mDiv;

    /// @brief Convert the tube to an implicit primitive representation.
    PrimitivePtr buildImplicitPrimitive() const;

    /// @brief Convert the tube to a mesh via UV construction.
    PrimitivePtr buildMeshPrimitive() const;
};
