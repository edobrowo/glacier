#include "geometry/polygon_soup.hpp"

PolygonSoup::PolygonSoup() : mPolygons() {
}

PolygonSoup::PolygonSoup(const ObjObject& obj) : mPolygons() {
    std::unordered_map<obj::FaceVertex, Index> vertex_map;
    mPolygons.reserve(obj.faces.size());

    for (const obj::Face& face : obj.faces) {
        mPolygons.push_back(Polygon{});

        Polygon& p = mPolygons.back();

        for (const obj::FaceVertex& fv : face.vertices) {
            p.vertices.push_back(Vertex{});

            Vertex& v = p.vertices.back();

            v.p = obj.vertexPositions[fv.position];

            if (fv.normal)
                v.n = obj.vertexNormals[*fv.normal];

            if (fv.texture)
                v.uv = Point2D(obj.vertexTexture[*fv.texture]);
        }
    }
}

const std::vector<PolygonSoup::Polygon>& PolygonSoup::polygons() const {
    return mPolygons;
}
