#pragma once

#include "geometry/geometry.hpp"
#include "material/material.hpp"
#include "primitive/primitive.hpp"
#include "scene_node.hpp"

class GeometryNode;

using GeometryNodePtr = std::unique_ptr<GeometryNode>;

/// @brief Scene node that contains a geometry and a material for local
/// illumination.
class GeometryNode : public SceneNode {
public:
    GeometryNode(
        const char* name, GeometryPtr&& geometry, MaterialPtr material
    );
    ~GeometryNode() = default;

    /// @brief Builds a primitive. The kind is specified with setPrimitiveKind.
    PrimitivePtr primitive() const;

    /// @brief Sets the primitive kind.
    void setPrimitiveKind(const Primitive::Kind kind);

    /// @brief Retrieves a constant reference to the geometry.
    const GeometryPtr& geometry() const;

    /// @brief Retrieves a constant reference to the material.
    const MaterialPtr& material() const;

protected:
    GeometryPtr mGeometry;
    MaterialPtr mMaterial;
    Primitive::Kind mPrimKind;
};
