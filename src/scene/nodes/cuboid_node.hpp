#pragma once

#include "geometry_node.hpp"

class CuboidNode : public GeometryNode {
public:
    CuboidNode(const char* name, MaterialPtr material);
    CuboidNode(
        const char* name,
        MaterialPtr material,
        const Point3D& Q,
        const Vector3D& x,
        const Vector3D& y,
        const Vector3D& z
    );
    ~CuboidNode() override;

    virtual void buildPrimitive() override;
};
