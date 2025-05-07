#include "primitive.hpp"

Primitive::Primitive() : mKind(Primitive::Kind::Null) {
}

Primitive::~Primitive() {
}

Option<Intersect> Primitive::intersect(const Ray& ray, const Interval& bounds)
    const {
    return std::nullopt;
}

Primitive::Kind Primitive::kind() const {
    return mKind;
}
