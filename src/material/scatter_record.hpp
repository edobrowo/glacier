#pragma once

#include "math/ray.hpp"
#include "math/vector.hpp"

/// @brief Material scattering record.
struct ScatterRecord {
    Ray scattered;
    Vector3D color;

    ScatterRecord(const Ray& ray, const Vector3D& color);
    ~ScatterRecord() = default;

    ScatterRecord(const ScatterRecord& other);
    ScatterRecord& operator=(const ScatterRecord& other);

    ScatterRecord(ScatterRecord&& other);
    ScatterRecord& operator=(ScatterRecord&& other);
};
