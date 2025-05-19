#include "geometry_node.hpp"

GeometryNode::GeometryNode(
    const char* name, GeometryPtr&& geometry, MaterialPtr material
)
    : SceneNode(name),
      mGeometry(std::move(geometry)),
      mMaterial(material),
      mPrimitive(nullptr),
      mPrimKind(Primitive::Kind::Mesh) {
    mKind = Kind::Geometry;
}

GeometryNode::~GeometryNode() {
}

const PrimitivePtr& GeometryNode::primitive() const {
    return mPrimitive;
}

void GeometryNode::setPrimitiveKind(const Primitive::Kind kind) {
    mPrimKind = kind;
}

const GeometryPtr& GeometryNode::geometry() const {
    return mGeometry;
}

const MaterialPtr& GeometryNode::material() const {
    return mMaterial;
}
