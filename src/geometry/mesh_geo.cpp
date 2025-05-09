#include "mesh_geo.hpp"

#include "primitive/mesh.hpp"

MeshGeo::MeshGeo() : mMesh() {
}

MeshGeo::MeshGeo(const IndexedMesh<VertexP>& mesh) : mMesh(mesh) {
}

PrimitivePtr MeshGeo::primitive(const Primitive::Kind kind) const {
    switch (kind) {
    case Primitive::Kind::Mesh:
        return buildMeshPrimitive();
    default:
        unreachable;
    }
}

PrimitivePtr MeshGeo::buildMeshPrimitive() const {
    return std::make_unique<Mesh>(mMesh);
}
