#include "geometry/disk.hpp"

#include "math/constants.hpp"

Disk::Disk() : Q(0, 0, 0.0), x(0.5, 0.0, 0.0), y(0.0, 0.5, 0.0) {
}

Disk::Disk(const Point3D& Q, const Vector3D& x, const Vector3D& y)
    : Q(Q), x(x), y(y) {
}

// TODO: normals and texture coordinates
TriangleMesh Disk::mesh() const {
    TriangleMesh mesh;

    const Point3D& center = Q;
    mesh.addVertex(Vertex{center});

    const Index a = 0;

    for (Index ui = 0; ui <= mDiv; ++ui) {
        const f64 u = static_cast<f64>(ui) / mDiv;
        const f64 theta = 2.0 * math::pi<f64>() * u;

        const Point3D p = Q + std::cos(theta) * x + std::sin(theta) * y;
        mesh.addVertex(Vertex{p});

        if (ui < mDiv) {
            const Index b = ui + 1;
            const Index c = ui + 2;

            mesh.addTriangle(a, b, c);
        }
    }

    return mesh;
}

void Disk::setDivisions(const Size div) {
    assertm(div > 0, "div must be greater than 0");

    mDiv = div;
}
