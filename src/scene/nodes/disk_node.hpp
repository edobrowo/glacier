#pragma once

#include "geometry_node.hpp"

class DiskNode : public GeometryNode {
public:
    DiskNode(const char* name, MaterialPtr material);
    DiskNode(
        const char* name,
        MaterialPtr material,
        const Point3D& Q,
        const Vector3D& u,
        const Vector3D& v
    );
    ~DiskNode() override = default;

    PrimitivePtr buildPrimitive() const override;

    void setDivisions(const Size div);
};
