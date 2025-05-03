#pragma once

#include "geometry_node.hpp"

class QuadNode : public GeometryNode {
public:
    QuadNode(const char* name, MaterialPtr material);
    QuadNode(const char* name,
             MaterialPtr material,
             const Point3D& Q,
             const Vector3D& u,
             const Vector3D& v);
    ~QuadNode() = default;
};
