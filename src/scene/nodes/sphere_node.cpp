#include "sphere_node.hpp"

#include "geometry/sphere_geo.hpp"

SphereNode::SphereNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<SphereGeo>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

SphereNode::SphereNode(
    const char* name,
    MaterialPtr material,
    const Point3D& center,
    const f64 radius
)
    : GeometryNode(
          name, std::make_unique<SphereGeo>(center, radius), material
      ) {
    mPrimKind = Primitive::Kind::Implicit;
}

void SphereNode::setDivisions(const Size u_div, const Size v_div) {
    SphereGeo* geo = static_cast<SphereGeo*>(mGeometry.get());
    geo->setDivisions(u_div, v_div);
}
