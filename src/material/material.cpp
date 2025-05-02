#include "material.hpp"

Material::Material() : mKind(Material::Kind::Null) {
}

Material::~Material() {
}

Option<ScatterRecord> Material::scatter(const Ray& incident,
                                        const Intersect& intersect) const {
    return std::nullopt;
}

Material::Kind Material::kind() const {
    return mKind;
}
