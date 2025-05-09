#include "geometry_node.hpp"

GeometryNode::GeometryNode(
    const char* name, GeometryPtr&& geometry, MaterialPtr material
)
    : SceneNode(name),
      mGeometry(std::move(geometry)),
      mMaterial(material),
      mPrimKind(Primitive::Kind::Mesh) {
    mKind = Kind::Geometry;
}

PrimitivePtr GeometryNode::primitive() const {
    return mGeometry->primitive(mPrimKind);
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
