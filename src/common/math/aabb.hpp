#pragma once

#include "math/interval.hpp"
#include "math/point.hpp"
#include "math/ray.hpp"
#include "util/format.hpp"

/// @brief Axis-aligned bounding box used for efficient intersection checks. The
/// bounding box is implemented using the slab method.
class AABB {
public:
    AABB();
    AABB(const Interval& x, const Interval& y, const Interval& z);
    AABB(const Point3D& p1, const Point3D& p2);

    ~AABB() = default;

    AABB(const AABB& other);
    AABB(AABB&& other);

    AABB& operator=(const AABB& other);
    AABB& operator=(AABB&& other);

    /// @brief Retrieves a point corresponding to the minimum AABB bound.
    Point3D min() const;

    /// @brief Retrieves a point corresponding to the maximum AABB bound.
    Point3D max() const;

    /// @brief Retrieve the interval for the corresponding axis.
    /// 0 correspond to the x-axis.
    /// 1 correspond to the y-axis.
    /// 2 correspond to the z-axis.
    const Interval& axis(const Index i) const;

    /// @brief Checks whether the ray intersects the bounding box.
    bool checkIntersect(const Ray& ray, const Interval& bounds) const;

    /// @brief Creates a new AABB that tightly encloses two AABBs.
    AABB enclosure(const AABB& other) const;

    /// @brief Creates a new AABB that is the intersection of two AABBs.
    AABB intersection(const AABB& other) const;

    /// @brief Minimum interval size for a bounding box axis.
    static constexpr f64 MINIMUM_AXIS_SIZE = 0.0001;

    union {
        struct {
            Interval x;
            Interval y;
            Interval z;
        };
        Interval axes[3];
    };

private:
    void padWithMinimum();
};

template <>
struct FormatWriter<AABB> {
    static void write(const AABB& value, StringBuffer& sb) {
        sb.appendFormat("[{},{}]", value.min(), value.max());
    }
};
