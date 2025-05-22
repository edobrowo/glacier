#pragma once

#include "material.hpp"

/// @brief Phong-based specular material.
class Specular : public Material {
public:
    Specular(const Vector3D& color, const f64 phong);
    ~Specular() override = default;

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a specular reflector controlled with a Phong
    /// coefficient.
    Option<ScatterRecord> scatter(
        const Ray& incident, const SurfaceInteraction& interaction
    ) const override;

private:
    Vector3D mColor;
    f64 mPhong;
};
