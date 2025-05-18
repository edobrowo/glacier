#include "material/emissive.hpp"

Emissive::Emissive(const Vector3D& color) : mColor(color) {
    mKind = Kind::Emissive;
}

Emissive::~Emissive() {
}

Vector3D Emissive::emitted() const {
    return mColor;
}
