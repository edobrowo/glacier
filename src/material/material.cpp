#include "material.hpp"

Material::Material() : mKind(Material::Kind::Null) {
}

Material::~Material() {
}

Material::Kind Material::kind() const {
    return mKind;
}
