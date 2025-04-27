#include "primitive.hpp"

Primitive::Primitive() : mKind(Primitive::Kind::Null) {
}

Primitive::~Primitive() {
}

Primitive::Kind Primitive::kind() const {
    return mKind;
}
