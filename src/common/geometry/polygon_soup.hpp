#pragma once

#include <map>
#include <vector>

#include "geometry/obj_parser.hpp"
#include "geometry/vertex.hpp"

/// @brief Polygon soup geometry representation.
class PolygonSoup {
public:
    /// @brief Polygon represented by an arbitrary sequence of vertices.
    struct Polygon {
        std::vector<Vertex> vertices;
    };

    PolygonSoup();
    explicit PolygonSoup(const ObjObject& obj);
    ~PolygonSoup() = default;

    /// @brief Retrieve a constant reference to the polygons in the soup.
    const std::vector<Polygon>& polygons() const;

private:
    std::vector<Polygon> mPolygons;
};

template <>
struct FormatWriter<PolygonSoup::Polygon> {
    static void write(const PolygonSoup::Polygon& p, StringBuffer& sb) {
        sb.append("P(");
        sb.appendFormat("vertices=[{}]", p.vertices);
        sb.putSafe(')');
    }
};

template <>
struct FormatWriter<PolygonSoup> {
    static void write(const PolygonSoup& mesh, StringBuffer& sb) {
        for (const PolygonSoup::Polygon& p : mesh.polygons())
            sb.appendFormat("{}\n", p);
    }
};
