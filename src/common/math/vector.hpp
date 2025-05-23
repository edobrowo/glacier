#pragma once

#include "math/normal.hpp"
#include "math/numeric.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

namespace {

template <typename T, u32 dim>
struct VectorData {
    const T* ptr() const {
        return components;
    }

protected:
    T components[dim];
};

}

template <Numeric T, u32 dim>
class Normal;

/// @brief Statically-sized vector class.
template <Numeric T, u32 dim>
class Vector : public VectorData<T, dim> {
public:
    using Data = VectorData<T, dim>;

    Vector();
    ~Vector() = default;

    explicit Vector(const T c1)
        requires(dim == 1);
    Vector(const T c1, const T c2)
        requires(dim == 2);
    Vector(const T c1, const T c2, const T c3)
        requires(dim == 3);
    Vector(const T c1, const T c2, const T c3, const T c4)
        requires(dim == 4);

    explicit Vector(const Vector<T, 3>& v)
        requires(dim == 2);
    explicit Vector(const Vector<T, 4>& v)
        requires(dim == 2);

    explicit Vector(const Vector<T, 4>& v)
        requires(dim == 3);
    Vector(const Vector<T, 2>& v, const T c1)
        requires(dim == 3);

    Vector(const Vector<T, 2>& v, const T c1, const T c2)
        requires(dim == 4);
    Vector(const Vector<T, 3>& v, const T c1)
        requires(dim == 4);

    Vector(const Vector<T, dim>& other);
    Vector<T, dim>& operator=(const Vector<T, dim>& other);

    explicit Vector(const Normal<T, 3>& other)
        requires(dim == 3);

    /// @brief Constructs the zero vector.
    static Vector<T, dim> zero();

    /// @brief Constructs the one vector.
    static Vector<T, dim> one();

    /// @brief Constructs a constant vector with the specified value.
    static Vector<T, dim> uniform(const T value);

    T operator[](const Index i) const;
    T& operator[](const Index i);

    Vector<T, dim>& operator+=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator+=(const Normal<T, dim>& rhs);
    Vector<T, dim>& operator-=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator-=(const Normal<T, dim>& rhs);
    Vector<T, dim>& operator*=(const T rhs);
    Vector<T, dim>& operator*=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator/=(const T rhs);
    Vector<T, dim>& operator/=(const Vector<T, dim>& rhs);

    /// @brief Determines the L2 norm of the vector.
    T length() const;

    /// @brief Determines the squared length of the vector.
    T dot() const;

    /// @brief Determines the dot product with another vector.
    T dot(const Vector<T, dim>& other) const;

    /// @brief Determines the dot product with another normal.
    T dot(const Normal<T, dim>& other) const;

    /// @brief Determines the cross product with another vector.
    Vector<T, dim> cross(const Vector<T, dim>& other) const
        requires(dim == 3);

    /// @brief Creates a new vector that is normalized.
    Vector<T, dim> normalize() const;

    /// @brief Creates a new vector consisting of the minimum components of two
    /// vectors.
    Vector<T, dim> min(const Vector<T, dim>& other) const;

    /// @brief Creates a new vector consisting of the maximum components of two
    /// vectors.
    Vector<T, dim> max(const Vector<T, dim>& other) const;

    /// @brief Creates a new vector clamped by the specified uniform bounds.
    Vector<T, dim> clamp(const T low, const T high) const;

    /// @brief Creates a new vector clamped by the specified vector bounds.
    Vector<T, dim> clamp(
        const Vector<T, dim>& low, const Vector<T, dim>& high
    ) const;

    /// @brief Retrieves a pointer to the components buffer.
    const T* data() const;

private:
    using Data::components;
};

using Vector2F = Vector<f32, 2>;
using Vector3F = Vector<f32, 3>;
using Vector4F = Vector<f32, 4>;

using Vector2D = Vector<f64, 2>;
using Vector3D = Vector<f64, 3>;
using Vector4D = Vector<f64, 4>;

using Vector2i = Vector<i32, 2>;
using Vector3i = Vector<i32, 3>;
using Vector4i = Vector<i32, 4>;

using Vector2u = Vector<u32, 2>;
using Vector3u = Vector<u32, 3>;
using Vector4u = Vector<u32, 4>;

template <typename T>
struct VectorData<T, 1> {
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
struct VectorData<T, 2> {
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
struct VectorData<T, 3> {
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
struct VectorData<T, 4> {
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
Vector<T, dim> Vector<T, dim>::zero() {
    Vector<T, dim> v;
    for (Index i = 0; i < dim; ++i)
        v.components[i] = T(0);
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::one() {
    Vector<T, dim> v;
    for (Index i = 0; i < dim; ++i)
        v.components[i] = T(1);
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::uniform(const T value) {
    Vector<T, dim> v;
    for (Index i = 0; i < dim; ++i)
        v.components[i] = value;
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector() {
    for (Index i = 0; i < dim; ++i)
        components[i] = T();
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const T c1)
    requires(dim == 1)
{
    components[0] = c1;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const T c1, const T c2)
    requires(dim == 2)
{
    components[0] = c1;
    components[1] = c2;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const T c1, const T c2, const T c3)
    requires(dim == 3)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const T c1, const T c2, const T c3, const T c4)
    requires(dim == 4)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
    components[3] = c4;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 3>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 4>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 4>& v)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 2>& v, const T c1)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 2>& v, const T c1, const T c2)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
    components[3] = c2;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, 3>& v, const T c1)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
    components[3] = c1;
}

template <Numeric T, u32 dim>
const T* Vector<T, dim>::data() const {
    return components;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Vector<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator=(const Vector<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector(const Normal<T, 3>& other)
    requires(dim == 3)
{
    ::memcpy(components, other.data(), dim * sizeof(T));
}

template <Numeric T, u32 dim>
T Vector<T, dim>::operator[](const Index i) const {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
T& Vector<T, dim>::operator[](const Index i) {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator+=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] += rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator+=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] += rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator-=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] -= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator-=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] -= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator*=(const T rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] *= rhs;
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator*=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] *= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator/=(const T rhs) {
    const T s = T(1) / rhs;
    for (Index i = 0; i < dim; ++i)
        components[i] *= s;
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator/=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] /= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator-(const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = -rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator+(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator+(const Vector<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator+(const Normal<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator-(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator-(const Vector<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator-(const Normal<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator*(const Vector<T, dim>& lhs, const T& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * rhs;
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator*(const T& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator/(const Vector<T, dim>& lhs, const T& rhs) {
    Vector<T, dim> result;
    const T s = T(1) / rhs;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * s;
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator/(const T& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator*(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> operator/(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
bool operator==(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <Numeric T, u32 dim>
bool operator!=(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    return !(lhs == rhs);
}

template <Numeric T, u32 dim>
T Vector<T, dim>::length() const {
    return std::sqrt(dot());
}

template <Numeric T, u32 dim>
T Vector<T, dim>::dot() const {
    return (*this).dot(*this);
}

template <Numeric T, u32 dim>
T Vector<T, dim>::dot(const Vector<T, dim>& other) const {
    T result = T(0);
    for (Index i = 0; i < dim; ++i)
        result += components[i] * other[i];
    return result;
}

template <Numeric T, u32 dim>
T Vector<T, dim>::dot(const Normal<T, dim>& other) const {
    T result = T(0);
    for (Index i = 0; i < dim; ++i)
        result += components[i] * other[i];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::cross(const Vector<T, dim>& other) const
    requires(dim == 3)
{
    Vector<T, dim> result;
    result[0] = components[1] * other[2] - components[2] * other[1];
    result[1] = components[2] * other[0] - components[0] * other[2];
    result[2] = components[0] * other[1] - components[1] * other[0];
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::normalize() const {
    return *this / length();
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::min(const Vector<T, dim>& other) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = std::min(components[i], other[i]);
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::max(const Vector<T, dim>& other) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = std::max(components[i], other[i]);
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::clamp(const T low, const T high) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = math::clamp(components[i], low, high);
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::clamp(
    const Vector<T, dim>& low, const Vector<T, dim>& high
) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = math::clamp(components[i], low[i], high[i]);
    return result;
}

template <Numeric T, u32 dim>
    requires FormatWritable<T>
struct FormatWriter<Vector<T, dim>> {
    static void write(const Vector<T, dim>& value, StringBuffer& sb) {
        sb.putSafe('(');
        for (Index i = 0; i < dim - 1; ++i)
            sb.appendFormat("{},", value[i]);
        sb.appendFormat("{}", value[dim - 1]);
        sb.putSafe(')');
    }
};
