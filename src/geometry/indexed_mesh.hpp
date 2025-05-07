#pragma once

#include <map>
#include <vector>

#include "obj_parser.hpp"
#include "vertex.hpp"

namespace std {

template <>
struct hash<obj::FaceVertex> {
    std::size_t operator()(const obj::FaceVertex& v) const {
        return (
            (std::hash<i64>()(v.position) << 1) ^
            (std::hash<Option<i64>>()(v.texture) << 2) ^
            std::hash<Option<i64>>()(v.normal)
        );
    }
};

}

struct IndexedTriangle {
    Index a, b, c;
};

template <typename Vertex>
class IndexedMesh {
public:
    IndexedMesh();
    explicit IndexedMesh(const ObjObject& obj);
    ~IndexedMesh() = default;

    const std::vector<Vertex>& vertices() const;
    const std::vector<IndexedTriangle>& triangles() const;

private:
    std::vector<Vertex> mVertices;
    std::vector<IndexedTriangle> mTriangles;
};

template <typename Vertex>
IndexedMesh<Vertex>::IndexedMesh() : mVertices(), mTriangles() {
}

template <typename Vertex>
IndexedMesh<Vertex>::IndexedMesh(const ObjObject& obj)
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

                mVertices[vi].position = obj.vertexPositions[v.position];

                if constexpr (requires { mVertices[vi].texture; }) {
                    if (v.texture)
                        mVertices[vi].texture = obj.vertexTexture[*v.texture];
                }

                if constexpr (requires { mVertices[vi].normal; }) {
                    if (v.normal)
                        mVertices[vi].normal = obj.vertexNormals[*v.normal];
                }
            }
        }

        const Index a = static_cast<Index>(vertex_map[face.vertices[0]]);
        const Index b = static_cast<Index>(vertex_map[face.vertices[1]]);
        const Index c = static_cast<Index>(vertex_map[face.vertices[2]]);
        mTriangles.push_back(IndexedTriangle{a, b, c});
    }
}

template <typename Vertex>
const std::vector<Vertex>& IndexedMesh<Vertex>::vertices() const {
    return mVertices;
}

template <typename Vertex>
const std::vector<IndexedTriangle>& IndexedMesh<Vertex>::triangles() const {
    return mTriangles;
}

template <>
struct FormatWriter<IndexedTriangle> {
    static void write(const IndexedTriangle& tri, StringBuffer& sb) {
        sb.append("Tri(", 4);
        sb.appendFormat("a={}, b={}, c={}", tri.a, tri.b, tri.c);
        sb.putSafe(')');
    }
};

template <typename Vertex>
    requires FormatWritable<Vertex>
struct FormatWriter<IndexedMesh<Vertex>> {
    static void write(const IndexedMesh<Vertex>& mesh, StringBuffer& sb) {
        sb.appendFormat(
            "Vertices: {}\nTriangles: {}", mesh.vertices(), mesh.triangles()
        );
    }
};
