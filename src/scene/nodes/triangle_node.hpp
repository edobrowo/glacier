#pragma once

#include "geometry_node.hpp"

class TriangleNode : public GeometryNode {
public:
    TriangleNode(const char* name, MaterialPtr material);
    TriangleNode(
        const char* name,
        MaterialPtr material,
        const Point3D& Q,
        const Vector3D& u,
        const Vector3D& v
    );
    ~TriangleNode() = default;
};
