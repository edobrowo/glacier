#include "geometry/triangle_mesh.hpp"

TriangleMesh::TriangleMesh() : mVertices(), mTriangles() {
}

TriangleMesh::TriangleMesh(const ObjObject& obj)
    : mVertices(obj.vertexPositions.size()), mTriangles() {
    std::unordered_map<obj::FaceVertex, Index> vertex_map;
    mTriangles.reserve(obj.faces.size());

    for (const obj::Face& face : obj.faces) {
        assertm(face.vertices.size() == 3, "face must have 3 vertices");

        for (Index i = 0; i < 3; ++i) {
            const obj::FaceVertex& v = face.vertices[i];
            if (vertex_map.find(v) == vertex_map.end()) {
                const Index vi = v.position;

                vertex_map[v] = vi;

                mVertices[vi].p = obj.vertexPositions[v.position];

                if (v.normal)
                    mVertices[vi].n = obj.vertexNormals[*v.normal];

                if (v.texture)
                    mVertices[vi].uv = Point2D(obj.vertexTexture[*v.texture]);
            }
        }

        const Index a = static_cast<Index>(vertex_map[face.vertices[0]]);
        const Index b = static_cast<Index>(vertex_map[face.vertices[1]]);
        const Index c = static_cast<Index>(vertex_map[face.vertices[2]]);
        mTriangles.push_back(Tri{a, b, c});
    }
}

const std::vector<Vertex>& TriangleMesh::vertices() const {
    return mVertices;
}

const std::vector<TriangleMesh::Tri>& TriangleMesh::triangles() const {
    return mTriangles;
}

void TriangleMesh::addVertex(const Vertex& v) {
    mVertices.emplace_back(v);
}

void TriangleMesh::addTriangle(const Index a, const Index b, const Index c) {
    mTriangles.emplace_back(a, b, c);
}
