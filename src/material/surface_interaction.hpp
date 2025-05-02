#pragma once

#include "material.hpp"
#include "primitive/intersect.hpp"

/// @brief Light ray-surface interaction record.
struct SurfaceInteraction {
    Intersect intersect;
    MaterialPtr material;

    SurfaceInteraction(const Intersect& intersect, MaterialPtr material);
    ~SurfaceInteraction() = default;

    SurfaceInteraction(const SurfaceInteraction& other);
    SurfaceInteraction operator=(const SurfaceInteraction& other);

    SurfaceInteraction(SurfaceInteraction&& other);
    SurfaceInteraction operator=(SurfaceInteraction&& other);
};
