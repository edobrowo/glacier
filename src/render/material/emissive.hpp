#pragma once

#include "material.hpp"

/// @brief Material that emits light.
class Emissive : public Material {
public:
    Emissive(const Vector3D& color);
    ~Emissive() override = default;

    /// @brief The emitted color of the light.
    Vector3D emitted() const;

private:
    Vector3D mColor;
};
