#include "mesh_prim.hpp"

#include "triangle_prim.hpp"

MeshPrim::MeshPrim(const IndexedMesh<VertexP>& mesh) : mMesh(mesh) {
    mKind = Kind::Mesh;
}

Option<SurfaceInteraction> MeshPrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    Option<SurfaceInteraction> closest = std::nullopt;

    for (const IndexedTriangle& tri : mMesh.triangles()) {
        const Point3D& Q = mMesh.vertices()[tri.a].position;
        const Point3D& R = mMesh.vertices()[tri.b].position;
        const Point3D& S = mMesh.vertices()[tri.c].position;

        const Vector3D u = R - Q;
        const Vector3D v = S - Q;

        if (const Option<SurfaceInteraction> i =
                TrianglePrim(Q, u, v).intersect(ray, bounds)) {
            if (!closest || i->t < closest->t)
                closest = i;
        }
    }

    return closest;
}
