#pragma once

#include "common/math/point.hpp"
#include "common/math/vector.hpp"
#include "material/material.hpp"

class Material;
using MaterialPtr = std::shared_ptr<Material>;

/// @brief Ray-surface interaction record.
struct SurfaceInteraction {
    enum class Face {
        Outside = 0,
        Inside
    };

    Point3D p;
    Vector3D n;
    Face face;
    MaterialPtr mat;
    f64 t;

    SurfaceInteraction(
        const Point3D& p, const Vector3D& n, const Face face, const f64 t
    );
    ~SurfaceInteraction() = default;

    SurfaceInteraction(const SurfaceInteraction& other);
    SurfaceInteraction operator=(const SurfaceInteraction& other);

    SurfaceInteraction(SurfaceInteraction&& other);
    SurfaceInteraction operator=(SurfaceInteraction&& other);
};
