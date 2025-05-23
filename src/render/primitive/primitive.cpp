#include "primitive.hpp"

Primitive::Primitive()
    : mKind(Primitive::Kind::Null),
      mObjectToWorld(),
      mMaterial(nullptr),
      mBbox() {
}

Primitive::~Primitive() {
}

Primitive::Kind Primitive::kind() const {
    return mKind;
}

const Transform& Primitive::objectToWorld() const {
    return mObjectToWorld;
}

void Primitive::setObjectToWorld(const Transform& transform) {
    mObjectToWorld = transform;
}

const MaterialPtr& Primitive::material() const {
    return mMaterial;
}

void Primitive::setMaterial(const MaterialPtr& material) {
    mMaterial = material;
}

const AABB& Primitive::aabb() const {
    return mBbox;
}
