#include "sphere_node.hpp"

#include "geometry/sphere.hpp"
#include "render/primitive/mesh_prim.hpp"
#include "render/primitive/sphere_prim.hpp"

SphereNode::SphereNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Sphere>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

SphereNode::SphereNode(
    const char* name,
    MaterialPtr material,
    const Point3D& center,
    const f64 radius
)
    : GeometryNode(name, std::make_unique<Sphere>(center, radius), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

SphereNode::~SphereNode() {
}

void SphereNode::setDivisions(const Size u_div, const Size v_div) {
    Sphere* geo = static_cast<Sphere*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
