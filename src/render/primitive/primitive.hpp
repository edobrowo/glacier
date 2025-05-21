#pragma once

#include "common/math/interval.hpp"
#include "common/math/matrix.hpp"
#include "common/math/ray.hpp"
#include "common/math/transform.hpp"
#include "common/prelude.hpp"
#include "render/material/material.hpp"
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

    /// @brief Retrieves a constant reference to the object transform.
    const Transform& objectToWorld() const;

    /// @brief Sets the object to world transform.
    void setObjectToWorld(const Transform& transform);

    /// @brief Retrieves a constant reference to the material pointer.
    const MaterialPtr& material() const;

    /// @brief Sets the material.
    void setMaterial(const MaterialPtr& material);

protected:
    Kind mKind;
    Transform mObjectToWorld;
    MaterialPtr mMaterial;
};

using PrimitivePtr = std::unique_ptr<Primitive>;
