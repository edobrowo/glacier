#pragma once

#include "geometry_node.hpp"

class SphereNode : public GeometryNode {
public:
    SphereNode(const char* name, MaterialPtr material);
    ~SphereNode() = default;
};
