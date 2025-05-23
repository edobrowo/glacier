#pragma once

#include <vector>

#include "common/prelude.hpp"
#include "render/material/surface_interaction.hpp"
#include "render/primitive/primitive.hpp"

class SpatialStructure {
public:
    SpatialStructure() = default;
    virtual ~SpatialStructure() = default;

    virtual void build(const std::vector<PrimitivePtr>& prims) = 0;

    virtual Option<SurfaceInteraction> intersect(const Ray& ray) const = 0;
};
