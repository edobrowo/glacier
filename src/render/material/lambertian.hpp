#pragma once

#include "material/material.hpp"

/// @brief Lambertian (pure diffuse) material.
class Lambertian : public Material {
public:
    explicit Lambertian(const Vector3D& color);
    virtual ~Lambertian();

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a cosine distributed diffuse material.
    virtual Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    Vector3D mColor;
};
