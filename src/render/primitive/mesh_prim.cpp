#include "mesh_prim.hpp"

#include "triangle_prim.hpp"

MeshPrim::MeshPrim(const TriangleMesh& mesh) : mMesh(mesh) {
    mKind = Kind::Mesh;

    if (mMesh.vertices().empty())
        return;

    Point3D min = mMesh.vertices().front().p;
    Point3D max = mMesh.vertices().front().p;

    for (Index i = 1; i < mMesh.vertices().size(); ++i) {
        const Point3D& p = mMesh.vertices()[i].p;
        min = min.min(p);
        max = max.max(p);
    }

    mBbox = AABB(min, max);
}

Option<SurfaceInteraction> MeshPrim::intersect(
    const Ray& ray, const Interval& bounds
) const {
    Option<SurfaceInteraction> closest = std::nullopt;

    for (const TriangleMesh::Tri& tri : mMesh.triangles()) {
        const Point3D& Q = mMesh.vertices()[tri.a].p;
        const Point3D& R = mMesh.vertices()[tri.b].p;
        const Point3D& S = mMesh.vertices()[tri.c].p;

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
