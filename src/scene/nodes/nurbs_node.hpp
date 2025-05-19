#pragma once

#include "geometry_node.hpp"

class NURBSNode : public GeometryNode {
public:
    NURBSNode(
        const char* name,
        MaterialPtr material,
        std::span<const Point3D> points,
        std::span<const f64> weights,
        std::span<const f64> u_knot_vector,
        std::span<const f64> v_knot_vector
    );
    ~NURBSNode() override;

    virtual void buildPrimitive() override;

    void setDivisions(const Size u_div, const Size v_div);
};
