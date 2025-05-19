#pragma once

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Disk geometry.
class Disk : public Geometry {
public:
    Disk();
    Disk(const Point3D& Q, const Vector3D& x, const Vector3D& y);
    ~Disk() = default;

    virtual TriangleMesh mesh() const override;

    /// @brief Set number of divisions for UV mesh construction
    void setDivisions(const Size div);

    Point3D Q;
    Vector3D x, y;

private:
    Size mDiv;
};
