#pragma once

/// @brief Base geometry class. All geometry subtypes support conversion to a
/// mesh.

#include "triangle_mesh.hpp"

class Geometry {
public:
    Geometry() = default;
    virtual ~Geometry();

    /// @brief Builds a triangle mesh corresponding to the geometry.
    virtual TriangleMesh mesh() const = 0;
};

using GeometryPtr = std::unique_ptr<Geometry>;
