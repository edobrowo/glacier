#pragma once

#include <map>
#include <vector>

#include "obj_parser.hpp"
#include "vertex.hpp"

/// @brief Polygon represented by an arbitrary sequence of vertices.
template <typename Vertex>
struct Polygon {
    std::vector<Vertex> vertices;
};

/// @brief Polygon soup geometry representation.
template <typename Vertex>
class PolygonSoup {
public:
    PolygonSoup();
    explicit PolygonSoup(const ObjObject& obj);
    ~PolygonSoup() = default;

    /// @brief Retrieve a constant reference to the polygons in the soup.
    const std::vector<Polygon<Vertex>>& polygons() const;

private:
    std::vector<Polygon<Vertex>> mPolygons;
};

template <typename Vertex>
PolygonSoup<Vertex>::PolygonSoup() : mPolygons() {
}

template <typename Vertex>
PolygonSoup<Vertex>::PolygonSoup(const ObjObject& obj) : mPolygons() {
    std::unordered_map<obj::FaceVertex, Index> vertex_map;
    mPolygons.reserve(obj.faces.size());

    for (const obj::Face& face : obj.faces) {
        mPolygons.push_back(Polygon<Vertex>{});

        Polygon<Vertex>& p = mPolygons.back();

        for (const obj::FaceVertex& fv : face.vertices) {
            p.vertices.push_back(Vertex{});

            Vertex& v = p.vertices.back();

            v.position = obj.vertexPositions[fv.position];

            if constexpr (requires { v.texture; }) {
                if (fv.texture)
                    v.texture = obj.vertexTexture[*fv.texture];
            }

            if constexpr (requires { v.normal; }) {
                if (fv.normal)
                    v.normal = obj.vertexNormals[*fv.normal];
            }
        }
    }
}

template <typename Vertex>
const std::vector<Polygon<Vertex>>& PolygonSoup<Vertex>::polygons() const {
    return mPolygons;
}

template <typename Vertex>
    requires FormatWritable<Vertex>
struct FormatWriter<Polygon<Vertex>> {
    static void write(const Polygon<Vertex>& p, StringBuffer& sb) {
        sb.append("P(", 2);
        sb.appendFormat("vertices=[{}]", p.vertices);
        sb.putSafe(')');
    }
};

template <typename Vertex>
    requires FormatWritable<Vertex>
struct FormatWriter<PolygonSoup<Vertex>> {
    static void write(const PolygonSoup<Vertex>& mesh, StringBuffer& sb) {
        for (const Polygon<Vertex>& p : mesh.polygons())
            sb.appendFormat("{}\n", p);
    }
};
