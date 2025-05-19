#pragma once

#include "common/geometry/triangle_mesh.hpp"
#include "primitive.hpp"

class MeshPrim : public Primitive {
public:
    MeshPrim(const TriangleMesh& mesh);
    ~MeshPrim() override = default;

    /// @brief Computes the surface intersection with the mesh by computing
    /// the intersection with all component triangles.
    virtual Option<SurfaceInteraction> intersect(
        const Ray& ray, const Interval& bounds
    ) const override;

private:
    TriangleMesh mMesh;
};
