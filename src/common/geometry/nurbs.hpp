#pragma once

#include <array>
#include <span>

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Control point.
struct NURBSControlPoint {
    Point3D point;
    f64 weight;
};

/// @brief NURBS patch geometry.
class NURBS : public Geometry {
public:
    static constexpr Size degree = 1;
    static constexpr Size numUPoints = 2;
    static constexpr Size numVPoints = 2;
    static constexpr Size numPoints = numUPoints * numVPoints;
    static constexpr Size numUKnots = numUPoints + degree + 1;
    static constexpr Size numVKnots = numVPoints + degree + 1;

    NURBS(
        std::span<const Point3D> points,
        std::span<const f64> weights,
        std::span<const f64> u_knot_vector,
        std::span<const f64> v_knot_vector
    );
    ~NURBS() override = default;

    TriangleMesh mesh() const override;

    /// @brief Retrieve a constant reference to the control points.
    const std::array<NURBSControlPoint, numPoints>& points() const;

    /// @brief Evaluate the NURBS patch at parameters (u, v).
    Point3D eval(const f64 u, const f64 v) const;

    /// @brief Set number of UV divisions for UV mesh construction.
    void setDivisions(const Size u_div, const Size v_div);

private:
    std::array<NURBSControlPoint, numPoints> mPoints;
    std::array<f64, numUKnots> mUKnots;
    std::array<f64, numVKnots> mVKnots;

    Size mUDiv, mVDiv;
};
