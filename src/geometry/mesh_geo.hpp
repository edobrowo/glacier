#pragma once

#include "geometry.hpp"
#include "indexed_mesh.hpp"
#include "math/point.hpp"
#include "primitive/primitive.hpp"
#include "util/common.hpp"

/// @brief Mesh geometry.
class MeshGeo : public Geometry {
public:
    MeshGeo();
    MeshGeo(const IndexedMesh<VertexP>& mesh);
    ~MeshGeo() = default;

    virtual PrimitivePtr buildPrimitive(
        const Primitive::Kind kind
    ) const override;

private:
    IndexedMesh<VertexP> mMesh;

    /// @brief Retrieve the mesh primitive.
    PrimitivePtr buildMeshPrimitive() const;
};
