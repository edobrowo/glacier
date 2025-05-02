#pragma once

#include "geometry_node.hpp"

class QuadNode : public GeometryNode {
public:
    QuadNode(const char* name, MaterialPtr material);
    ~QuadNode() = default;
};
