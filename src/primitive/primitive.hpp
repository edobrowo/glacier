#pragma once

#include "intersect.hpp"
#include "math/interval.hpp"
#include "math/ray.hpp"
#include "util/common.hpp"

/// @brief Rendering primitive base class. Defines an interface for ray-surface
/// intersections.
class Primitive {
public:
    enum class Kind {
        Null = 0,
        Sphere,
    };

    Primitive();
    virtual ~Primitive();

    /// @brief Determines the closest intersect between a ray and primitive
    /// within the specified parameter bounds.
    virtual Option<Intersect> intersect(const Ray& ray,
                                        const Interval& bounds) const;

    /// @brief Retrieves the kind of the primitive.
    Kind kind() const;

protected:
    Kind mKind;
};

using PrimitivePtr = std::unique_ptr<Primitive>;
