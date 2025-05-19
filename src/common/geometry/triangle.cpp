#include "geometry/triangle.hpp"

#include "math/constants.hpp"

Triangle::Triangle()
    : Q(Point3D(-0.5, -0.5, 0.0)),
      x(Vector3D(1.0, 0.0, 0.0)),
      y(Vector3D(0.0, 1.0, 0.0)) {
}

Triangle::Triangle(const Point3D& Q, const Vector3D& u, const Vector3D& v)
    : Q(Q), x(u), y(v) {
}

TriangleMesh Triangle::mesh() const {
    TriangleMesh mesh;

    mesh.addVertex(Vertex{Q});
    mesh.addVertex(Vertex{Q + x});
    mesh.addVertex(Vertex{Q + y});

    mesh.addTriangle(0, 1, 2);

    return mesh;
}
