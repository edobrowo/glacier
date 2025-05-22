#pragma once

#include "material.hpp"

/// @brief Dielectric material. Parameterized by the ratio if the material's
/// refractive index over the refractive index of the enclosing media.
class Dielectric : public Material {
public:
    explicit Dielectric(const f64 eta);
    ~Dielectric() override = default;

    /// @brief Scatters the incident ray via refraction.
    Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    f64 mEta;
};
