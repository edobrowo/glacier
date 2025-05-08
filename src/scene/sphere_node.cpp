#include "sphere_node.hpp"

#include "geometry/sphere_geo.hpp"

SphereNode::SphereNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Sphere>(), material) {
}

SphereNode::SphereNode(
    const char* name,
    MaterialPtr material,
    const Point3D& center,
    const f64 radius
)
    : GeometryNode(name, std::make_unique<Sphere>(center, radius), material) {
    mGeo = SphereGeo(center, radius);
}

void SphereNode::renderAsImplicit() {
    mPrimitive = mGeo.toImplicitPrimitive();
}

void SphereNode::renderAsMesh(const Size u_div, const Size v_div) {
    mPrimitive = mGeo.toMeshPrimitive(u_div, v_div);
}
