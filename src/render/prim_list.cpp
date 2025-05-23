#include "prim_list.hpp"

PrimList::PrimList() : mPrimitives() {
}

void PrimList::build(const std::vector<PrimitivePtr>& prims) {
    mPrimitives = prims;
}

Option<SurfaceInteraction> PrimList::intersect(const Ray& ray) const {
    // Current closest intersection and interval.
    Option<SurfaceInteraction> closest = std::nullopt;
    Interval bounds(0.001, math::infinity<f64>());

    for (const PrimitivePtr& primitive : mPrimitives) {
        const Transform& object_to_world = primitive->objectToWorld();
        const Transform world_to_object = invert(object_to_world);

        // Transform the ray with the primitive's world to object
        // transformation.
        const Ray inverse_ray = world_to_object(ray);

        // Compute the surface interaction with the current primitive.
        if (const Option<SurfaceInteraction> interaction =
                primitive->intersect(inverse_ray, bounds)) {
            if (!closest || interaction->t < closest->t) {
                closest = interaction;

                closest->p = object_to_world(interaction->p);
                closest->n = (object_to_world(interaction->n)).normalize();
                closest->mat = primitive->material();

                bounds.max = std::min(closest->t, bounds.max);
            }
        }
    }

    return closest;
}
