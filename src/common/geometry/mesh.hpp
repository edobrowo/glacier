#pragma once

#include "geometry/geometry.hpp"
#include "geometry/triangle_mesh.hpp"
#include "math/point.hpp"
#include "prelude.hpp"

/// @brief Mesh geometry.
class Mesh : public Geometry {
public:
    Mesh();
    Mesh(const TriangleMesh& mesh);
    ~Mesh() = default;

    virtual TriangleMesh mesh() const override;

private:
    TriangleMesh mMesh;
};
