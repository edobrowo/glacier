#pragma once

#include "math/vector.hpp"
#include "prelude.hpp"

/// @brief Raster image class.
class Image {
public:
    Image(const Size width, const Size height);
    ~Image();

    /// @brief Sets the color of pixel (i, j). Color values are normalized to
    /// integer values along [0, 255].
    void set(const Index i, const Index j, const Vector3D& color);

    /// @brief Saves the image as a PNG to the specified path.
    void save(const char* path) const;

private:
    Size mWidth;
    Size mHeight;
    u8* mData;
};
