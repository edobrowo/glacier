#pragma once

#include "material.hpp"

class Specular : public Material {
public:
    Specular(const Vector3D& color, const f64 phong);
    ~Specular() = default;

    /// @brief Scatters the incident ray where the material appearance
    /// properties correspond to a specular reflector controlled with a Phong
    /// coefficient.
    virtual ScatterRecord scatter(const Ray& incident,
                                  const Intersect& intersect) const override;

private:
    Vector3D mColor;
    f64 mPhong;
};
