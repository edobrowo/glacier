#pragma once

#include <string>

#include "geometry_node.hpp"

class MeshNode : public GeometryNode {
public:
    MeshNode(const char* name, MaterialPtr material, const char* path);
    ~MeshNode() override;
};
