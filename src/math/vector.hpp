#pragma once

#include "numeric.hpp"
#include "util/common.hpp"
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
class Vector : public VectorData<T, dim> {
public:
    using Data = VectorData<T, dim>;

    /// @brief Constructs a 1D vector with the specified component.
    explicit Vector(const T c1)
        requires(dim == 1);

    /// @brief Constructs a 2D vector with the specified components.
    Vector(const T c1, const T c2)
        requires(dim == 2);

    /// @brief Constructs a 3D vector with the specified components.
    Vector(const T c1, const T c2, const T c3)
        requires(dim == 3);

    /// @brief Constructs a 4D vector with the specified components.
    Vector(const T c1, const T c2, const T c3, const T c4)
        requires(dim == 4);

    ~Vector() = default;

    Vector(const Vector<T, dim>& other);
    Vector<T, dim>& operator=(const Vector<T, dim>& other);

    /// @brief Constructs the zero vector.
    static Vector<T, dim> zero();

    /// @brief Constructs the one vector.
    static Vector<T, dim> one();

    /// @brief Constructs a constant vector with the specified value.
    static Vector<T, dim> uniform(const T value);

    T operator[](const Index i) const;
    T& operator[](const Index i);

    Vector<T, dim>& operator+=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator-=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator*=(const T rhs);
    Vector<T, dim>& operator*=(const Vector<T, dim>& rhs);
    Vector<T, dim>& operator/=(const T rhs);
    Vector<T, dim>& operator/=(const Vector<T, dim>& rhs);

    /// @brief Determines whether the vector is a zero vector.
    bool isZero() const;

    /// @brief Determines the squared length of the vector.
    T lengthSqr() const;

    /// @brief Determines the L2 norm of the vector.
    T length() const;

    /// @brief Creates a new vector that is normalized.
    Vector<T, dim> normalized() const;

    /// @brief Creates a new vector clamped by the specified uniform bounds.
    Vector<T, dim> clamped(const T low, const T high) const;

    /// @brief Creates a new vector clamped by the specified vector bounds.
    Vector<T, dim> clamped(const Vector<T, dim>& low,
                           const Vector<T, dim>& high) const;

    /// @brief Retrieves a pointer to the components buffer.
    const T* data() const;

private:
    Vector();

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
    for (Index i = 0; i < dim; ++i) v.components[i] = T(0);
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::one() {
    Vector<T, dim> v;
    for (Index i = 0; i < dim; ++i) v.components[i] = T(1);
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::uniform(const T value) {
    Vector<T, dim> v;
    for (Index i = 0; i < dim; ++i) v.components[i] = value;
    return v;
}

template <Numeric T, u32 dim>
Vector<T, dim>::Vector() {
    for (Index i = 0; i < dim; ++i) components[i] = T();
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
    for (Index i = 0; i < dim; ++i) components[i] += rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator-=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i) components[i] -= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator*=(const T rhs) {
    for (Index i = 0; i < dim; ++i) components[i] *= rhs;
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator*=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i) components[i] *= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator/=(const T rhs) {
    for (Index i = 0; i < dim; ++i) components[i] /= rhs;
    return *this;
}

template <Numeric T, u32 dim>
Vector<T, dim>& Vector<T, dim>::operator/=(const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i) components[i] /= rhs.components[i];
    return *this;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator-(const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = -rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator+(const Vector<T, dim>& lhs,
                                const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] + rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator-(const Vector<T, dim>& lhs,
                                const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] - rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator*(const Vector<T, dim>& lhs, const T& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] * rhs;
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator*(const T& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator/(const Vector<T, dim>& lhs, const T& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] / rhs;
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator/(const T& lhs, const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator*(const Vector<T, dim>& lhs,
                                const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] * rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static Vector<T, dim> operator/(const Vector<T, dim>& lhs,
                                const Vector<T, dim>& rhs) {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i) result[i] = lhs[i] / rhs[i];
    return result;
}

template <Numeric T, u32 dim>
static bool operator==(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    for (Index i = 0; i < dim; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <Numeric T, u32 dim>
static bool operator!=(const Vector<T, dim>& lhs, const Vector<T, dim>& rhs) {
    return !(lhs == rhs);
}

template <Numeric T, u32 dim>
bool Vector<T, dim>::isZero() const {
    for (Index i = 0; i < dim; ++i)
        if (components[i] != T(0))
            return false;
    return true;
}

template <Numeric T, u32 dim>
T dot(Vector<T, dim> lhs, Vector<T, dim> rhs) {
    T result = T(0);
    for (Index i = 0; i < dim; ++i) result += T(lhs[i]) * T(rhs[i]);
    return result;
}

template <Numeric T, u32 dim>
T Vector<T, dim>::lengthSqr() const {
    return dot(*this, *this);
}

template <Numeric T, u32 dim>
T Vector<T, dim>::length() const {
    return ::sqrt(lengthSqr());
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::normalized() const {
    return *this / length();
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::clamped(const T low, const T high) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = math::clamp(components[i], low, high);
    return result;
}

template <Numeric T, u32 dim>
Vector<T, dim> Vector<T, dim>::clamped(const Vector<T, dim>& low,
                                       const Vector<T, dim>& high) const {
    Vector<T, dim> result;
    for (Index i = 0; i < dim; ++i)
        result[i] = math::clamp(components[i], low[i], high[i]);
    return result;
}

template <Numeric T>
Vector<T, 3> cross(Vector<T, 3> lhs, Vector<T, 3> rhs) {
    Vector<T, 3> result;
    result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return result;
}

template <Numeric T>
    requires FormatWritable<T>
struct FormatWriter<Vector<T, 2>> {
    static void write(const Vector<T, 2>& value, StringBuffer& sb) {
        format(sb, "({},{})", value[0], value[1]);
    }
};

template <Numeric T>
    requires FormatWritable<T>
struct FormatWriter<Vector<T, 3>> {
    static void write(const Vector<T, 3>& value, StringBuffer& sb) {
        format(sb, "({},{},{})", value[0], value[1], value[2]);
    }
};

template <Numeric T>
    requires FormatWritable<T>
struct FormatWriter<Vector<T, 4>> {
    static void write(const Vector<T, 4>& value, StringBuffer& sb) {
        format(sb, "({},{},{},{})", value[0], value[1], value[2], value[3]);
    }
};

template <Numeric T, u32 dim>
    requires FormatWritable<T>
struct FormatWriter<Vector<T, dim>> {
    static void write(const Vector<T, dim>& value, StringBuffer& sb) {
        sb.append("(");
        for (Index i = 0; i < dim - 1; ++i) sb.appendFormat("{},", value[i]);
        sb.appendFormat("{}", value[dim - 1]);
        sb.append(")");
    }
};
