#include "material/scatter_record.hpp"

ScatterRecord::ScatterRecord(const Ray& ray, const Vector3D& color)
    : scattered(ray), color(color) {
}

ScatterRecord::ScatterRecord(const ScatterRecord& other)
    : scattered(other.scattered), color(other.color) {
}

ScatterRecord& ScatterRecord::operator=(const ScatterRecord& other) {
    scattered = other.scattered;
    color = other.color;

    return *this;
}

ScatterRecord::ScatterRecord(ScatterRecord&& other)
    : scattered(std::move(other.scattered)), color(std::move(other.color)) {
}

ScatterRecord& ScatterRecord::operator=(ScatterRecord&& other) {
    scattered = std::move(other.scattered);
    color = std::move(other.color);

    return *this;
}
