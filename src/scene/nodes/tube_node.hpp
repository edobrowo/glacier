#pragma once

#include "geometry_node.hpp"

class TubeNode : public GeometryNode {
public:
    TubeNode(const char* name, MaterialPtr material);
    TubeNode(
        const char* name,
        MaterialPtr material,
        const Point3D& base,
        const f64 radius,
        const f64 height
    );
    ~TubeNode() override = default;

    PrimitivePtr buildPrimitive() const override;

    void setCapVisibility(const bool top, const bool bottom);
    void setDivisions(const Size div);
};
