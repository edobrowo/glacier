#pragma once

#include "geometry/intersect.hpp"
#include "material.hpp"

/// @brief Light ray-surface interaction record.
struct SurfaceInteraction {
    Intersect intersect;
    MaterialTempPtr material;

    SurfaceInteraction(const Intersect& intersect, MaterialTempPtr material);
    ~SurfaceInteraction() = default;

    SurfaceInteraction(const SurfaceInteraction& other);
    SurfaceInteraction operator=(const SurfaceInteraction& other);

    SurfaceInteraction(SurfaceInteraction&& other);
    SurfaceInteraction operator=(SurfaceInteraction&& other);
};
