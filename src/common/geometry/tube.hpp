#pragma once

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Tube geometry.
class Tube : public Geometry {
public:
    Tube();
    Tube(const Point3D& center, const f64 radius, const f64 height);
    ~Tube() = default;

    virtual TriangleMesh mesh() const override;

    /// @brief Center of the tube.
    Point3D center() const;

    /// @brief Radius of the tube.
    f64 radius() const;

    /// @brief Height of the tube.
    f64 height() const;

    /// @brief Top cap visibility;
    bool topCapVisible() const;

    /// @brief Bottom cap visibility;
    bool bottomCapVisible() const;

    /// @brief Set cap visibility.
    void setCapVisibility(const bool top, const bool bottom);

    /// @brief Set number of divisions for UV mesh construction
    void setDivisions(const Size div);

private:
    Point3D mCenter;
    f64 mRadius, mHeight;
    bool mTopCap, mBottomCap;
    Size mDiv;
};
