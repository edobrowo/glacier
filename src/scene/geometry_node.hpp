#pragma once

#include "geometry/primitive.hpp"
#include "material/material.hpp"
#include "scene_node.hpp"

class GeometryNode;

using GeometryNodePtr = std::unique_ptr<GeometryNode>;

/// @brief Geometry scene node. Holds a rendering primitive.
class GeometryNode : public SceneNode {
public:
    GeometryNode(const char* name,
                 PrimitivePtr&& primitive,
                 MaterialPtr&& material);
    ~GeometryNode() = default;

    /// @brief Constructs a GeometryNodePtr.
    static GeometryNodePtr make(const char* name,
                                PrimitivePtr&& primitive,
                                MaterialPtr&& material);

    /// @brief Retrieves a constant reference to the primitive.
    const PrimitivePtr& primitive() const;

    /// @brief Retrieves a constant reference to the material.
    const MaterialPtr& material() const;

private:
    PrimitivePtr mPrimitive;
    MaterialPtr mMaterial;
};
