#pragma once

#include "math/numeric.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

namespace {

template <typename T, u32 dim>
struct NormalData {
    const T* ptr() const {
        return components;
    }

protected:
    T components[dim];
};

}

template <Numeric T, u32 dim>
class Vector;

/// @brief Statically-sized surface normal class.
template <Numeric T, u32 dim>
class Normal : public NormalData<T, dim> {
public:
    using Data = NormalData<T, dim>;

    Normal();
    ~Normal() = default;

    explicit Normal(const T c1)
        requires(dim == 1);
    Normal(const T c1, const T c2)
        requires(dim == 2);
    Normal(const T c1, const T c2, const T c3)
        requires(dim == 3);
    Normal(const T c1, const T c2, const T c3, const T c4)
        requires(dim == 4);

    explicit Normal(const Normal<T, 3>& v)
        requires(dim == 2);
    explicit Normal(const Normal<T, 4>& v)
        requires(dim == 2);

    explicit Normal(const Normal<T, 4>& v)
        requires(dim == 3);
    Normal(const Normal<T, 2>& v, const T c1)
        requires(dim == 3);

    Normal(const Normal<T, 2>& v, const T c1, const T c2)
        requires(dim == 4);
    Normal(const Normal<T, 3>& v, const T c1)
        requires(dim == 4);

    Normal(const Normal<T, dim>& other);
    Normal<T, dim>& operator=(const Normal<T, dim>& other);

    explicit Normal(const Vector<T, 3>& other)
        requires(dim == 3);

    T operator[](const Index i) const;
    T& operator[](const Index i);

    Normal<T, dim>& operator+=(const Normal<T, dim>& rhs);
    Normal<T, dim>& operator-=(const Normal<T, dim>& rhs);
    Normal<T, dim>& operator*=(const T rhs);
    Normal<T, dim>& operator*=(const Normal<T, dim>& rhs);
    Normal<T, dim>& operator/=(const T rhs);
    Normal<T, dim>& operator/=(const Normal<T, dim>& rhs);

    /// @brief Determines the L2 norm of the normal.
    T length() const;

    /// @brief Determines the squared length of the normal.
    T dot() const;

    /// @brief Determines the dot product with another normal.
    T dot(const Normal<T, dim>& other) const;

    /// @brief Determines the dot product with another vector.
    T dot(const Vector<T, dim>& other) const;

    /// @brief Creates a new normal that is normalized.
    Normal<T, dim> normalize() const;

    /// @brief Retrieves a pointer to the components buffer.
    const T* data() const;

private:
    using Data::components;
};

using Normal2F = Normal<f32, 2>;
using Normal3F = Normal<f32, 3>;
using Normal4F = Normal<f32, 4>;

using Normal2D = Normal<f64, 2>;
using Normal3D = Normal<f64, 3>;
using Normal4D = Normal<f64, 4>;

using Normal2i = Normal<i32, 2>;
using Normal3i = Normal<i32, 3>;
using Normal4i = Normal<i32, 4>;

using Normal2u = Normal<u32, 2>;
using Normal3u = Normal<u32, 3>;
using Normal4u = Normal<u32, 4>;

template <typename T>
struct NormalData<T, 1> {
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
struct NormalData<T, 2> {
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
struct NormalData<T, 3> {
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
struct NormalData<T, 4> {
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
Normal<T, dim>::Normal() {
    for (Index i = 0; i < dim; ++i)
        components[i] = T();
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const T c1)
    requires(dim == 1)
{
    components[0] = c1;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const T c1, const T c2)
    requires(dim == 2)
{
    components[0] = c1;
    components[1] = c2;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const T c1, const T c2, const T c3)
    requires(dim == 3)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const T c1, const T c2, const T c3, const T c4)
    requires(dim == 4)
{
    components[0] = c1;
    components[1] = c2;
    components[2] = c3;
    components[3] = c4;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 3>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 4>& v)
    requires(dim == 2)
{
    components[0] = v.x;
    components[1] = v.y;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 4>& v)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 2>& v, const T c1)
    requires(dim == 3)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 2>& v, const T c1, const T c2)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = c1;
    components[3] = c2;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, 3>& v, const T c1)
    requires(dim == 4)
{
    components[0] = v.x;
    components[1] = v.y;
    components[2] = v.z;
    components[3] = c1;
}

template <Numeric T, u32 dim>
const T* Normal<T, dim>::data() const {
    return components;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Normal<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator=(const Normal<T, dim>& other) {
    ::memcpy(components, other.components, dim * sizeof(T));
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>::Normal(const Vector<T, 3>& other)
    requires(dim == 3)
{
    ::memcpy(components, other.data(), dim * sizeof(T));
}

template <Numeric T, u32 dim>
T Normal<T, dim>::operator[](const Index i) const {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
T& Normal<T, dim>::operator[](const Index i) {
    assertm(i < dim, "i not less than dim");
    return components[i];
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator+=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] += rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator-=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] -= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator*=(const T rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] *= rhs;
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator*=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] *= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator/=(const T rhs) {
    const T s = T(1) / rhs;
    for (Index i = 0; i < dim; ++i)
        components[i] *= s;
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim>& Normal<T, dim>::operator/=(const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        components[i] /= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator-(const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = -rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator+(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator-(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator*(const Normal<T, dim>& lhs, const T& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * rhs;
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator*(const T& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator/(const Normal<T, dim>& lhs, const T& rhs) {
    Normal<T, dim> result;
    const T s = T(1) / rhs;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * s;
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator/(const T& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator*(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> operator/(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    Normal<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = lhs[i] / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
bool operator==(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <Numeric T, u32 dim>
bool operator!=(const Normal<T, dim>& lhs, const Normal<T, dim>& rhs) {
    return !(lhs == rhs);
}

template <Numeric T, u32 dim>
T Normal<T, dim>::length() const {
    return std::sqrt(dot());
}

template <Numeric T, u32 dim>
T Normal<T, dim>::dot() const {
    return (*this).dot(*this);
}

template <Numeric T, u32 dim>
T Normal<T, dim>::dot(const Normal<T, dim>& other) const {
    T result = T(0);
    for (Index i = 0; i < dim; ++i)
        result += components[i] * other[i];
    return result;
}

template <Numeric T, u32 dim>
T Normal<T, dim>::dot(const Vector<T, dim>& other) const {
    T result = T(0);
    for (Index i = 0; i < dim; ++i)
        result += components[i] * other[i];
    return result;
}

template <Numeric T, u32 dim>
Normal<T, dim> Normal<T, dim>::normalize() const {
    return *this / length();
}

template <Numeric T, u32 dim>
    requires FormatWritable<T>
struct FormatWriter<Normal<T, dim>> {
    static void write(const Normal<T, dim>& value, StringBuffer& sb) {
        sb.putSafe('(');
        for (Index i = 0; i < dim - 1; ++i)
            sb.appendFormat("{},", value[i]);
        sb.appendFormat("{}", value[dim - 1]);
        sb.append(")^T");
    }
};
