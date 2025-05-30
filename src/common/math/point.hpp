#pragma once

#include "math/numeric.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

namespace {

template <typename T, u32 dim>
struct PointData {
    const T* ptr() const {
        return components;
    }

protected:
    T components[dim];
};

}

/// @brief Statically-sized point class.
template <Numeric T, u32 dim>
class Point : public PointData<T, dim> {
public:
    using Data = PointData<T, dim>;

    Point();
    ~Point() = default;

    explicit Point(const T c1)
        requires(dim == 1);
    Point(const T c1, const T c2)
        requires(dim == 2);
    Point(const T c1, const T c2, const T c3)
        requires(dim == 3);
    Point(const T c1, const T c2, const T c3, const T c4)
        requires(dim == 4);

    explicit Point(const Point<T, 3>& v)
        requires(dim == 2);
    explicit Point(const Point<T, 4>& v)
        requires(dim == 2);

    explicit Point(const Point<T, 4>& v)
        requires(dim == 3);
    Point(const Point<T, 2>& v, const T c1)
        requires(dim == 3);

    Point(const Point<T, 2>& v, const T c1, const T c2)
        requires(dim == 4);
    Point(const Point<T, 3>& v, const T c1)
        requires(dim == 4);

    Point(const Point<T, dim>& other);
    Point<T, dim>& operator=(const Point<T, dim>& other);

    explicit Point(const Vector<T, dim>& v);

    Point<T, dim>& operator+=(const Vector<T, dim>& rhs);
    Point<T, dim>& operator-=(const Vector<T, dim>& rhs);

    /// @brief Constructs the point at (0, 0, 0).
    static Point<T, dim> zero();

    /// @brief Constructs a point with all components set to the specified
    /// value.
    static Point<T, dim> uniform(const T value);

    T operator[](const Index i) const;
    T& operator[](const Index i);

    /// @brief Builds the position vector corresponding to this point.
    Vector<T, dim> pos() const;

    /// @brief Creates a new point consisting of the minimum components of two
    /// vectors.
    Point<T, dim> min(const Point<T, dim>& other) const;

    /// @brief Creates a new point consisting of the maximum components of two
    /// vectors.
    Point<T, dim> max(const Point<T, dim>& other) const;

    /// @brief Retrieves a pointer to the components buffer.
    const T* data() const;

private:
    using Data::components;
};

using Point2F = Point<f32, 2>;
using Point3F = Point<f32, 3>;
using Point4F = Point<f32, 4>;

using Point2D = Point<f64, 2>;
using Point3D = Point<f64, 3>;
using Point4D = Point<f64, 4>;

using Point2i = Point<i32, 2>;
using Point3i = Point<i32, 3>;
using Point4i = Point<i32, 4>;

using Point2u = Point<u32, 2>;
using Point3u = Point<u32, 3>;
using Point4u = Point<u32, 4>;

template <typename T>
struct PointData<T, 1> {
    union {
        struct {
            T x;
        };
        T components[1];
    };

    const T* data() const {
        return components;
    }
};

template <typename T>
struct PointData<T, 2> {
    union {
        struct {
            T x, y;
        };
        T components[2];
    };

    const T* data() const {
        return components;
    }
};

template <typename T>
struct PointData<T, 3> {
    union {
        struct {
            T x, y, z;
        };
        T components[3];
    };

    const T* data() const {
        return components;
    }
};

template <typename T>
struct PointData<T, 4> {
    union {
        struct {
            T x, y, z, w;
        };
        T components[4];
    };

    const T* data() const {
        return components;
    }
};

template <Numeric T, u32 dim>
Point<T, dim> Point<T, dim>::zero() {
    Point<T, dim> v;
    for (Index i = 0; i < dim; ++i)
        v.components[i] = T(0);
    return v;
}

template <Numeric T, u32 dim>
Point<T, dim> Point<T, dim>::uniform(const T value) {
    Point<T, dim> v;
    for (Index i = 0; i < dim; ++i)
        v.components[i] = value;
    return v;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point() {
    for (Index i = 0; i < dim; ++i)
        components[i] = T();
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const T c1)
    requires(dim == 1)
{
    components[0] = c1;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const T c1, const T c2)
    requires(dim == 2)
{
    components[0] = c1;
    components[1] = c2;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const T c1, const T c2, const T c3)
    requires(dim == 3)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const T c1, const T c2, const T c3, const T c4)
    requires(dim == 4)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
    components[3] = c4;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 3>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 4>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 4>& v)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 2>& v, const T c1)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 2>& v, const T c1, const T c2)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
    components[3] = c2;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, 3>& v, const T c1)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
    components[3] = c1;
}

template <Numeric T, u32 dim>
const T* Point<T, dim>::data() const {
    return components;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Point<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
}

template <Numeric T, u32 dim>
Point<T, dim>& Point<T, dim>::operator=(const Point<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
    return *this;
}

template <Numeric T, u32 dim>
Point<T, dim>::Point(const Vector<T, dim>& v) {
    ::memcpy(components, v.data(), dim * sizeof(T));
}

template <Numeric T, u32 dim>
Point<T, dim>& Point<T, dim>::operator+=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] += rhs[i];
    return *this;
}

template <Numeric T, u32 dim>
Point<T, dim>& Point<T, dim>::operator-=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] -= rhs[i];
    return *this;
}

template <Numeric T, u32 dim>
T Point<T, dim>::operator[](const Index i) const {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
T& Point<T, dim>::operator[](const Index i) {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
Point<T, dim> operator+(const Point<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Point<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Point<T, dim> operator+(const Vector<T, dim>& lhs, const Point<T, dim>& rhs) {
    Point<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Point<T, dim> operator-(const Point<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Point<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator-(const Point<T, dim>& lhs, const Point<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Point<T, dim>::pos() const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = components[i];
    return result;
}

template <Numeric T, u32 dim>
Point<T, dim> Point<T, dim>::min(const Point<T, dim>& other) const {
    Point<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = std::min(components[i], other[i]);
    return result;
}

template <Numeric T, u32 dim>
Point<T, dim> Point<T, dim>::max(const Point<T, dim>& other) const {
    Point<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = std::max(components[i], other[i]);
    return result;
}

template <Numeric T, u32 dim>
T dist(const Point<T, dim>& lhs, const Point<T, dim>& rhs) {
    return (lhs.pos() - rhs.pos()).length();
}

template <Numeric T, u32 dim>
Point<T, dim> blend(
    const T t, const Point<T, dim>& lhs, const Point<T, dim>& rhs
) {
    assertm(T(0) <= t && t <= T(1), "t must be in [0, 1]");

    Point<T, dim> result;

    const T t_inv = T(1) - t;
    result[0] = t_inv * lhs[0] + t * rhs[0];
    result[1] = t_inv * lhs[1] + t * rhs[1];
    result[2] = t_inv * lhs[2] + t * rhs[2];

    return result;
}

template <Numeric T, u32 dim>
    requires FormatWritable<T>
struct FormatWriter<Point<T, dim>> {
    static void write(const Point<T, dim>& value, StringBuffer& sb) {
        sb.putSafe('(');
        for (Index i = 0; i < dim - 1; ++i)
            sb.appendFormat("{},", value[i]);
        sb.appendFormat("{}", value[dim - 1]);
        sb.putSafe(')');
    }
};
