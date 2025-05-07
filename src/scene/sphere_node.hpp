#pragma once

#include "geometry_node.hpp"

class SphereNode : public GeometryNode {
public:
    SphereNode(const char* name, MaterialPtr material);
    SphereNode(
        const char* name,
        MaterialPtr material,
        const Point3D& center,
        const f64 radius
    );
    ~SphereNode() = default;
};
