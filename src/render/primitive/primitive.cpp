#include "primitive.hpp"

Primitive::Primitive()
    : mKind(Primitive::Kind::Null), mObjectToWorld(), mMaterial(nullptr) {
}

Primitive::~Primitive() {
}

Option<SurfaceInteraction> Primitive::intersect(
    const Ray& ray, const Interval& bounds
) const {
    return std::nullopt;
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
