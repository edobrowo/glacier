#pragma once

#include "primitive/primitive.hpp"

/// @brief Base geometry class. All geometry subtypes support conversion to a
/// rendering primitive.
class Geometry {
public:
    Geometry() = default;
    virtual ~Geometry();

    /// @brief Builds a primitive corresponding to the geometry.
    /// @param kind Rendering primitive kind.
    /// @return Unique pointer to the primitive.
    virtual PrimitivePtr primitive(const Primitive::Kind kind) const = 0;
};

using GeometryPtr = std::unique_ptr<Geometry>;
