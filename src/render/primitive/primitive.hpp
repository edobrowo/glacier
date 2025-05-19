#pragma once

#include "common/math/interval.hpp"
#include "common/math/ray.hpp"
#include "common/prelude.hpp"
#include "render/material/surface_interaction.hpp"

/// @brief Rendering primitive base class. Defines an interface for ray-surface
/// intersections.
class Primitive {
public:
    enum class Kind {
        Null = 0,
        Implicit,
        Mesh,
    };

    Primitive();
    virtual ~Primitive();

    /// @brief Determines the closest intersect between a ray and primitive
    /// within the specified parameter bounds.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const;

    /// @brief Retrieves the kind of the primitive.
    Kind kind() const;

protected:
    Kind mKind;
};

using PrimitivePtr = std::unique_ptr<Primitive>;
