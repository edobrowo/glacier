#pragma once

#include "material.hpp"

/// @brief Dielectric material. Parameterized by the ratio if the material's
/// refractive index over the refractive index of the enclosing media.
class Dielectric : public Material {
public:
    explicit Dielectric(const f64 eta);
    virtual ~Dielectric();

    /// @brief Scatters the incident ray via refraction.
    virtual Option<ScatterRecord> scatter(
        const Ray& incident, const Intersect& intersect
    ) const override;

private:
    f64 mEta;
};
