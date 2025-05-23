#pragma once

#include "common/prelude.hpp"
#include "primitive/primitive.hpp"
#include "render/spatial_structure.hpp"

class BVHNode {
public:
    BVHNode() = default;
    virtual ~BVHNode() = default;

    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const = 0;

    virtual AABB aabb() const = 0;
};

using BVHNodePtr = std::shared_ptr<BVHNode>;

class BVHPrim : public BVHNode {
public:
    explicit BVHPrim(const PrimitivePtr& prim);
    ~BVHPrim() override = default;

    Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

    AABB aabb() const override;

private:
    PrimitivePtr mPrimitive;
};

class BVHBranch : public BVHNode {
public:
    BVHBranch(const BVHNodePtr& left, const BVHNodePtr& right);
    ~BVHBranch() override = default;

    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

    AABB aabb() const override;

private:
    BVHNodePtr mLeft;
    BVHNodePtr mRight;
    AABB mBbox;
};

class BVH : public SpatialStructure {
public:
    BVH();
    ~BVH() override = default;

    void build(const std::vector<PrimitivePtr>& prims) override;

    Option<SurfaceInteraction> intersect(const Ray& ray) const override;

private:
    BVHNodePtr buildRecursive(std::span<PrimitivePtr> prims) const;

    BVHNodePtr mRoot;
};
