#pragma once

#include "geometry_node.hpp"

class BezierPatchNode : public GeometryNode {
public:
    BezierPatchNode(
        const char* name,
        MaterialPtr material,
        const std::array<Point3D, 16>& control_points
    );
    ~BezierPatchNode() override = default;

    void setDivisions(const Size u_div, const Size v_div);
};
