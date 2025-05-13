#pragma once

#include <array>
#include <span>

#include "geometry.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Bezier patch geometry.
class BezierPatchGeo : public Geometry {
public:
    BezierPatchGeo(std::span<const Point3D> points);
    ~BezierPatchGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

    /// @brief Retrieve a constant reference to the control points.
    const std::array<Point3D, 16>& points() const;

    /// @brief Evaluate the Bezier patch at parameters (u, v).
    Point3D eval(const f64 u, const f64 v) const;

    /// @brief Set number of UV divisions for UV mesh construction.
    void setDivisions(const Size u_div, const Size v_div);

private:
    std::array<Point3D, 16> mPoints;
    Size mUDiv, mVDiv;

    /// @brief Convert the Bezier patch to a mesh via UV construction.
    PrimitivePtr buildMeshPrimitive() const;
};
