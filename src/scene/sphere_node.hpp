#pragma once

#include "geometry/sphere_geo.hpp"
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

    void renderAsImplicit();
    void renderAsMesh(const Size u_div, const Size v_div);

private:
    SphereGeo mGeo;
};
