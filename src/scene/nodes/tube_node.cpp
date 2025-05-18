#include "tube_node.hpp"

#include "geometry/tube_geo.hpp"

TubeNode::TubeNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<TubeGeo>(), material) {
    mPrimKind = Primitive::Kind::Implicit;
}

TubeNode::TubeNode(
    const char* name,
    MaterialPtr material,
    const Point3D& base,
    const f64 radius,
    const f64 height
)
    : GeometryNode(
          name, std::make_unique<TubeGeo>(base, radius, height), material
      ) {
    mPrimKind = Primitive::Kind::Implicit;
}

void TubeNode::setCapVisibility(const bool top, const bool bottom) {
    TubeGeo* geo = static_cast<TubeGeo*>(mGeometry.get());
    geo->setCapVisibility(top, bottom);
}

void TubeNode::setDivisions(const Size div) {
    TubeGeo* geo = static_cast<TubeGeo*>(mGeometry.get());
    geo->setDivisions(div);
}
