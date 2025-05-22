#pragma once

#include "geometry/geometry.hpp"
#include "render/material/material.hpp"
#include "render/primitive/primitive.hpp"
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
    virtual ~GeometryNode() override;

    /// @brief Retrieves a constant reference to the geometry.
    const GeometryPtr& geometry() const;

    /// @brief Retrieves a constant reference to the material.
    const MaterialPtr& material() const;

    /// @brief Retrieves the primitive kind.
    Primitive::Kind primitiveKind() const;

    /// @brief Sets the primitive kind.
    void setPrimitiveKind(const Primitive::Kind kind);

    /// @brief Sets the cached primitive.
    void setPrimitive(PrimitivePtr&& prim) {
        mPrimitive = std::move(prim);
    }

    /// @brief Retrieves the cached primitive.
    const PrimitivePtr& primitive() const {
        return mPrimitive;
    }

protected:
    GeometryPtr mGeometry;
    MaterialPtr mMaterial;
    PrimitivePtr mPrimitive;
    Primitive::Kind mPrimitiveKind;
};
