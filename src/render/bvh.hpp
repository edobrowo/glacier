#pragma once

#include "common/prelude.hpp"
#include "primitive/primitive.hpp"
#include "render/spatial_structure.hpp"

/// @brief Generic BVH node.
class BVHNode {
public:
    BVHNode() = default;
    virtual ~BVHNode() = default;

    /// @brief Computes the intersection with the subtree rooted at this node.
    /// Checks the intersection with the AABB before traversal.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const = 0;

    /// @brief Retrieves the AABB of this BVH subtree.
    virtual AABB aabb() const = 0;
};

using BVHNodePtr = std::shared_ptr<BVHNode>;

/// @brief BVH leaf node. Holds a primitive.
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

/// @brief BVH branch node. Holds two child BVH nodes.
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

/// @brief Bounding Volume Hierarchy (BVH) spatial acceleration structure.
class BVH : public SpatialStructure {
public:
    BVH();
    ~BVH() override = default;

    void build(const std::vector<PrimitivePtr>& prims) override;

    Option<SurfaceInteraction> intersect(const Ray& ray) const override;

private:
    /// @brief Recursively constructs the BVH tree.
    BVHNodePtr buildRecursive(std::span<PrimitivePtr> prims) const;

    BVHNodePtr mRoot;
};
