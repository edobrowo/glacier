#pragma once

#include "geometry/indexed_mesh.hpp"
#include "primitive.hpp"

class Mesh : public Primitive {
public:
    Mesh();
    Mesh(const IndexedMesh<VertexP>& mesh);
    ~Mesh() override = default;

    /// @brief Computes the surface intersection with the mesh by computing
    /// the intersection with all component triangles.
    virtual Option<Intersect> intersect(const Ray& ray, const Interval& bounds)
        const override;

private:
    IndexedMesh<VertexP> mMesh;
};
