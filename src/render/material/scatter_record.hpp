#pragma once

#include "common/math/ray.hpp"
#include "common/math/vector.hpp"

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
