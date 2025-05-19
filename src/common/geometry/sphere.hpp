#pragma once

#include "geometry/geometry.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Sphere geometry.
class Sphere : public Geometry {
public:
    Sphere();
    Sphere(const Point3D& center, const f64 radius);
    ~Sphere() = default;

    virtual TriangleMesh mesh() const override;

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
};
