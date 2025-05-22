#include "material.hpp"

Material::Material() : mKind(Material::Kind::Null) {
}

Option<ScatterRecord> Material::scatter(
    const Ray& incident, const SurfaceInteraction& interaction
) const {
    return std::nullopt;
}

Material::Kind Material::kind() const {
    return mKind;
}
