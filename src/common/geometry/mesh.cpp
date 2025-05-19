#include "geometry/mesh.hpp"

Mesh::Mesh() : mMesh() {
}

Mesh::Mesh(const TriangleMesh& mesh) : mMesh(mesh) {
}

TriangleMesh Mesh::mesh() const {
    return mMesh;
}
