#include "image.hpp"

#include <iomanip>
#include <sstream>

#include "util/log.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Image::Image(const Size width, const Size height)
    : mWidth(width), mHeight(height), mData(new u8[width * height * 3]) {
}

Image::~Image() {
    delete[] mData;
}

void Image::set(const Index i, const Index j, const Vector3D& color) {
    assertm(i < mWidth, "i must be less than image width");
    assertm(j < mHeight, "j must be less than image height");

    mData[3 * (j * mWidth + i)] = static_cast<u8>(color.x * 255.0);
    mData[3 * (j * mWidth + i) + 1] = static_cast<u8>(color.y * 255.0);
    mData[3 * (j * mWidth + i) + 2] = static_cast<u8>(color.z * 255.0);
}

void Image::save(const char* path) const {
    if (mData == nullptr) {
        Log::f("mData is null");
        return;
    }

    const int error = stbi_write_png(
        path,
        static_cast<int>(mWidth),
        static_cast<int>(mHeight),
        3,
        mData,
        static_cast<int>(mWidth * 3)
    );

    if (!error)
        Log::f("Failed to save image");
}
