#pragma once

#include "render/spatial_structure.hpp"

class PrimList : public SpatialStructure {
public:
    PrimList();
    ~PrimList() override = default;

    void build(const std::vector<PrimitivePtr>& prims) override;

    Option<SurfaceInteraction> intersect(const Ray& ray) const override;

private:
    std::vector<PrimitivePtr> mPrimitives;
};
