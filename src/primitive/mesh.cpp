#include "mesh.hpp"

#include "triangle.hpp"

Mesh::Mesh() : mMesh() {
    mKind = Kind::Mesh;
}

Mesh::Mesh(const IndexedMesh<VertexP>& mesh) : mMesh(mesh) {
    mKind = Kind::Mesh;
}

Option<Intersect> Mesh::intersect(const Ray& ray, const Interval& bounds)
    const {
    Option<Intersect> closest = std::nullopt;

    for (const IndexedTriangle& tri : mMesh.triangles()) {
        const Point3D& Q = mMesh.vertices()[tri.a].position;
        const Point3D& R = mMesh.vertices()[tri.b].position;
        const Point3D& S = mMesh.vertices()[tri.c].position;

        const Vector3D u = R - Q;
        const Vector3D v = S - Q;

        if (const Option<Intersect> i =
                Triangle(Q, u, v).intersect(ray, bounds)) {
            if (!closest || i->t < closest->t)
                closest = i;
        }
    }

    return closest;
}
