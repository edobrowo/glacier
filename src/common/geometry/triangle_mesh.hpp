#pragma once

#include <map>
#include <vector>

#include "geometry/obj_parser.hpp"
#include "geometry/vertex.hpp"

/// @brief Triangle mesh geometry representation.
class TriangleMesh {
public:
    /// @brief Triangle represented by 3 vertex indices.
    struct Tri {
        Index a, b, c;
    };

    TriangleMesh();
    explicit TriangleMesh(const ObjObject& obj);
    ~TriangleMesh() = default;

    /// @brief Retrieve a constant reference to the vertex array.
    const std::vector<Vertex>& vertices() const;

    /// @brief Retrieve a constant reference to the array of indexed triangles.
    const std::vector<Tri>& triangles() const;

    /// @brief Add a vertex to the mesh.
    void addVertex(const Vertex& v);

    /// @brief Create a triangle from the vertices at the given indices.
    void addTriangle(const Index a, const Index b, const Index c);

private:
    std::vector<Vertex> mVertices;
    std::vector<Tri> mTriangles;
};

template <>
struct FormatWriter<TriangleMesh::Tri> {
    static void write(const TriangleMesh::Tri& tri, StringBuffer& sb) {
        sb.append("Tri(");
        sb.appendFormat("a={}, b={}, c={}", tri.a, tri.b, tri.c);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<TriangleMesh> {
    static void write(const TriangleMesh& mesh, StringBuffer& sb) {
        sb.appendFormat(
            "Vertices: {}\nTriangles: {}", mesh.vertices(), mesh.triangles()
        );
    }
};
