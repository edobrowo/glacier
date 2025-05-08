#pragma once

#include <array>
#include <span>

#include "indexed_mesh.hpp"
#include "math/point.hpp"
#include "util/common.hpp"

class BezierPatch {
public:
    BezierPatch(std::span<const Point3D> points);
    ~BezierPatch() = default;

    const std::array<Point3D, 16>& points() const;

    Point3D eval(const f64 u, const f64 v) const;

    template <typename Vertex>
    IndexedMesh<Vertex> mesh(const Size u_div, const Size v_div);

private:
    std::array<Point3D, 16> mPoints;
};

#include "util/format.hpp"

// TODO: normals and texture coordinates
template <typename Vertex>
IndexedMesh<Vertex> BezierPatch::mesh(const Size u_div, const Size v_div) {
    assertm(u_div > 1, "u_div must be greater than 1");
    assertm(v_div > 1, "v_div must be greater than 1");

    IndexedMesh<Vertex> m;
    for (Index ui = 0; ui < u_div; ++ui) {
        const f64 u = static_cast<f64>(ui) / u_div;

        for (Index vi = 0; vi < v_div; ++vi) {
            const f64 v = static_cast<f64>(vi) / v_div;

            const Point3D& p = eval(u, v);

            m.addVertex(Vertex{p});

            if ((ui < u_div - 1) && (vi < v_div - 1)) {
                const Index a1 = ui * u_div + vi;
                const Index a2 = ui * v_div + (vi + 1);
                const Index a3 = (ui + 1) * v_div + (vi + 1);
                m.addTriangle(a1, a2, a3);

                const Index b1 = ui * u_div + vi;
                const Index b2 = (ui + 1) * v_div + (vi + 1);
                const Index b3 = (ui + 1) * v_div + vi;
                m.addTriangle(b1, b2, b3);
            }
        }
    }

    return m;
}
