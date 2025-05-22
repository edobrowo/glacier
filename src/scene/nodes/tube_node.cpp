#include "tube_node.hpp"

#include "geometry/tube.hpp"
#include "render/primitive/mesh_prim.hpp"
#include "render/primitive/tube_prim.hpp"

TubeNode::TubeNode(const char* name, MaterialPtr material)
    : GeometryNode(name, std::make_unique<Tube>(), material) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

TubeNode::TubeNode(
    const char* name,
    MaterialPtr material,
    const Point3D& base,
    const f64 radius,
    const f64 height
)
    : GeometryNode(
          name, std::make_unique<Tube>(base, radius, height), material
      ) {
    mPrimitiveKind = Primitive::Kind::Implicit;
}

TubeNode::~TubeNode() {
}

PrimitivePtr TubeNode::buildPrimitive() const {
    switch (mPrimitiveKind) {
    case Primitive::Kind::Mesh: {
        return std::make_unique<MeshPrim>(mGeometry->mesh());
    }
    case Primitive::Kind::Implicit: {
        const Tube* tube = static_cast<Tube*>(mGeometry.get());
        return std::make_unique<TubePrim>(
            tube->center(),
            tube->radius(),
            tube->height(),
            tube->topCapVisible(),
            tube->bottomCapVisible()
        );
    }
    default:
        unimplemented;
    }
}

void TubeNode::setCapVisibility(const bool top, const bool bottom) {
    Tube* geo = static_cast<Tube*>(mGeometry.get());
    geo->setCapVisibility(top, bottom);
}

void TubeNode::setDivisions(const Size div) {
    Tube* geo = static_cast<Tube*>(mGeometry.get());
    geo->setDivisions(div);
}
