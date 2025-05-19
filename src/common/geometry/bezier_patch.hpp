#pragma once

#include <array>
#include <span>

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Bezier patch geometry.
class BezierPatch : public Geometry {
public:
    BezierPatch(std::span<const Point3D> points);
    ~BezierPatch() = default;

    virtual TriangleMesh mesh() const override;

    /// @brief Retrieve a constant reference to the control points.
    const std::array<Point3D, 16>& points() const;

    /// @brief Evaluate the Bezier patch at parameters (u, v).
    Point3D eval(const f64 u, const f64 v) const;

    /// @brief Set number of UV divisions for UV mesh construction.
    void setDivisions(const Size u_div, const Size v_div);

private:
    std::array<Point3D, 16> mPoints;
    Size mUDiv, mVDiv;
};
