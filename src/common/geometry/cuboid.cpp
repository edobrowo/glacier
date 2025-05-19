#include "geometry/cuboid.hpp"

#include "math/constants.hpp"

Cuboid::Cuboid()
    : Q(-0.5, -0.5, -0.5),
      x(1.0, 0.0, 0.0),
      y(0.0, 1.0, 0.0),
      z(0.0, 0.0, 1.0) {
}

Cuboid::Cuboid(
    const Point3D& Q, const Vector3D& x, const Vector3D& y, const Vector3D& z
)
    : Q(Q), x(x), y(y), z(z) {
}

// TODO: normals and texture coordinates
TriangleMesh Cuboid::mesh() const {
    TriangleMesh mesh;

    mesh.addVertex(Vertex{Q});
    mesh.addVertex(Vertex{Q + x});
    mesh.addVertex(Vertex{Q + y});
    mesh.addVertex(Vertex{Q + x + y});

    mesh.addVertex(Vertex{Q + z});
    mesh.addVertex(Vertex{Q + z + x});
    mesh.addVertex(Vertex{Q + z + y});
    mesh.addVertex(Vertex{Q + z + x + y});

    // Front face (-Z).
    mesh.addTriangle(0, 2, 3);
    mesh.addTriangle(0, 3, 1);

    // Back face (+Z).
    mesh.addTriangle(4, 5, 7);
    mesh.addTriangle(4, 7, 6);

    // Left face (-X).
    mesh.addTriangle(4, 6, 2);
    mesh.addTriangle(4, 2, 0);

    // Right face (+X).
    mesh.addTriangle(1, 3, 7);
    mesh.addTriangle(1, 7, 5);

    // Top face (+Y).
    mesh.addTriangle(2, 6, 7);
    mesh.addTriangle(2, 7, 3);

    // Bottom face (-Y).
    mesh.addTriangle(4, 0, 1);
    mesh.addTriangle(4, 1, 5);

    return mesh;
}
