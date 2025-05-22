#pragma once

#include "material.hpp"

/// @brief Lambertian (pure diffuse) material.
class Lambertian : public Material {
public:
    explicit Lambertian(const Vector3D& color);
    ~Lambertian() override = default;

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a cosine distributed diffuse material.
    Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    Vector3D mColor;
};
