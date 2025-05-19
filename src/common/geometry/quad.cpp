#include "geometry/quad.hpp"

#include "math/constants.hpp"

Quad::Quad()
    : Q(Point3D(-0.5, -0.5, 0.0)),
      x(Vector3D(1.0, 0.0, 0.0)),
      y(Vector3D(0.0, 1.0, 0.0)) {
}

Quad::Quad(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : Q(Q), x(u), y(v) {
}

// TODO: normals and texture coordinates
TriangleMesh Quad::mesh() const {
    TriangleMesh mesh;

    mesh.addVertex(Vertex{Q});
    mesh.addVertex(Vertex{Q + x});
    mesh.addVertex(Vertex{Q + y});
    mesh.addVertex(Vertex{Q + x + y});

    mesh.addTriangle(0, 1, 3);
    mesh.addTriangle(0, 3, 2);

    return mesh;
}
