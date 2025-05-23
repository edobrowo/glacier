#include "bvh.hpp"

#include <algorithm>

#include "common/util/thread_random.hpp"

BVHPrim::BVHPrim(const PrimitivePtr& prim) : mPrimitive(prim) {
}

Option<SurfaceInteraction> BVHPrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    const Transform& object_to_world = mPrimitive->objectToWorld();
    const Transform world_to_object = invert(object_to_world);

    // Transform the ray with the primitive's world to object
    // transformation.
    const Ray inverse_ray = world_to_object(ray);

    if (!mPrimitive->aabb().checkIntersect(inverse_ray, bounds))
        return std::nullopt;

    // Compute the surface interaction with the current primitive.
    if (Option<SurfaceInteraction> interaction =
            mPrimitive->intersect(inverse_ray, bounds)) {
        interaction->p = object_to_world(interaction->p);
        interaction->n = (object_to_world(interaction->n)).normalize();
        interaction->mat = mPrimitive->material();

        return interaction;
    }

    return std::nullopt;
}

AABB BVHPrim::aabb() const {
    return mPrimitive->objectToWorld()(mPrimitive->aabb());
}

BVHBranch::BVHBranch(const BVHNodePtr& left, const BVHNodePtr& right)
    : mLeft(left), mRight(right), mBbox(left->aabb().enclosure(right->aabb())) {
}

Option<SurfaceInteraction> BVHBranch::intersect(
    const Ray& ray, const Interval& bounds
) const {
    if (!mBbox.checkIntersect(ray, bounds))
        return std::nullopt;

    const Option<SurfaceInteraction> si1 = mLeft->intersect(ray, bounds);
    const Option<SurfaceInteraction> si2 =
        mRight->intersect(ray, Interval(bounds.min, si1 ? si1->t : bounds.max));

    if (!si1)
        return si2;
    if (!si2)
        return si1;
    return (si1->t < si2->t) ? si1 : si2;
}

AABB BVHBranch::aabb() const {
    return mBbox;
}

namespace {

bool boxAxisCompare(
    const PrimitivePtr& left, const PrimitivePtr& right, const u32 ax
) {
    assertm(ax < 3, "axis must be 0, 1, or 2");
    return left->aabb().axis(ax).min < right->aabb().axis(ax).min;
}

};

BVH::BVH() : mRoot(nullptr) {
}

void BVH::build(const std::vector<PrimitivePtr>& prims) {
    std::vector<PrimitivePtr> copy = prims;
    mRoot = buildRecursive(std::span<PrimitivePtr>(copy));
}

Option<SurfaceInteraction> BVH::intersect(const Ray& ray) const {
    const Interval bounds(0.001, math::infinity<f64>());
    return mRoot->intersect(ray, bounds);
}

BVHNodePtr BVH::buildRecursive(std::span<PrimitivePtr> prims) const {
    if (prims.size() == 1)
        return std::make_shared<BVHPrim>(prims.front());

    if (prims.size() == 2) {
        BVHNodePtr left = std::make_shared<BVHPrim>(prims.front());
        BVHNodePtr right = std::make_shared<BVHPrim>(prims.back());
        return std::make_shared<BVHBranch>(left, right);
    }

    // TODO: Improved splitting.
    const u32 ax = static_cast<u32>(std::floor(thread_rng::uniform(0.0, 3.0)));
    auto comparator = [ax](
                          const PrimitivePtr& left, const PrimitivePtr& right
                      ) { return boxAxisCompare(left, right, ax); };

    std::sort(std::begin(prims), std::end(prims), comparator);

    const Index middle = prims.size() / 2;
    std::span<PrimitivePtr> prims_left = prims.subspan(0, middle);
    std::span<PrimitivePtr> prims_right = prims.subspan(middle);

    BVHNodePtr left = buildRecursive(prims_left);
    BVHNodePtr right = buildRecursive(prims_right);
    return std::make_shared<BVHBranch>(left, right);
}
