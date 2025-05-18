#pragma once

#include "geometry/geometry.hpp"
#include "geometry/indexed_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"
#include "primitive/primitive.hpp"

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
