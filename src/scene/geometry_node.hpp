#pragma once

#include "material/material.hpp"
#include "primitive/primitive.hpp"
#include "scene_node.hpp"

class GeometryNode;

using GeometryNodePtr = std::unique_ptr<GeometryNode>;

/// @brief Scene node that contains a primitive and a material for local
/// illumination.
class GeometryNode : public SceneNode {
public:
    GeometryNode(
        const char* name, PrimitivePtr&& primitive, MaterialPtr material
    );
    ~GeometryNode() = default;

    /// @brief Retrieves a constant reference to the primitive.
    const PrimitivePtr& primitive() const;

    /// @brief Retrieves a constant reference to the material.
    const MaterialPtr& material() const;

protected:
    PrimitivePtr mPrimitive;
    MaterialPtr mMaterial;
};
