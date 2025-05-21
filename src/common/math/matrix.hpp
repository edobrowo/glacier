#pragma once

#include "math/numeric.hpp"
#include "math/point.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"

/// @brief Statically-sized matrix class.
template <std::floating_point T, u32 p, u32 q>
class Matrix {
public:
    Matrix();
    ~Matrix() = default;

    /// @brief Constructs a matrix of all zeros.
    static Matrix<T, p, q> zero();

    /// @brief Constructs a matrix of all ones.
    static Matrix<T, p, q> one();

    /// @brief Constructs a constant matrix with the specified value.
    static Matrix<T, p, q> uniform(const T value);

    /// @brief Constructs a diagonal matrix wuth the specified value.
    static Matrix<T, p, q> diag(const T value)
        requires(p == q);

    /// @brief Constructs the identity matrix.
    static Matrix<T, p, q> ident()
        requires(p == q);

    explicit Matrix(const std::array<T, p * q>& elements);

    explicit Matrix(const Matrix<T, 3, 3>& m)
        requires(p == 2 && q == 2);
    explicit Matrix(const Matrix<T, 4, 4>& m)
        requires(p == 2 && q == 2);

    explicit Matrix(const Matrix<T, 4, 4>& m)
        requires(p == 3 && q == 3);

    Matrix(const Matrix<T, p, q>& other);
    Matrix<T, p, q>& operator=(const Matrix<T, p, q>& other);

    /// @brief Retrieves the element at the specified row and column.
    T operator()(const Index row, const Index col) const;

    /// @brief Retrieves a mutable reference to the specified element.
    T& operator()(const Index row, const Index col);

    Matrix<T, p, q>& operator+=(const Matrix<T, p, q>& rhs);
    Matrix<T, p, q>& operator-=(const Matrix<T, p, q>& rhs);
    Matrix<T, p, q>& operator*=(const T& rhs);
    Matrix<T, p, q>& operator*=(const Matrix<T, p, q>& rhs)
        requires(p == q);
    Matrix<T, p, q>& operator/=(const T& rhs);

    /// @brief Retrieves a pointer to the elements buffer.
    const T* data() const;

    /// @brief Retrieves a mutable pointer to the elements buffer.
    T* dataMutable();

private:
    T mElements[p * q];
};

using Matrix2D = Matrix<f64, 2, 2>;
using Matrix3D = Matrix<f64, 3, 3>;
using Matrix4D = Matrix<f64, 4, 4>;

using Matrix2F = Matrix<f32, 2, 2>;
using Matrix3F = Matrix<f32, 3, 3>;
using Matrix4F = Matrix<f32, 4, 4>;

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix() : mElements() {
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q> Matrix<T, p, q>::zero() {
    return Matrix<T, p, q>::uniform(T(0));
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q> Matrix<T, p, q>::one() {
    return Matrix<T, p, q>::uniform(T(1));
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q> Matrix<T, p, q>::uniform(const T value) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = value;
    return result;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q> Matrix<T, p, q>::diag(const T value)
    requires(p == q)
{
    Matrix<T, p, q> result;
    for (Index i = 0; i < p; ++i)
        result(i, i) = value;
    return result;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q> Matrix<T, p, q>::ident()
    requires(p == q)
{
    return Matrix<T, p, q>::diag(T(1));
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix(const std::array<T, p * q>& elements) {
    ::memcpy(mElements, elements.data(), p * q * sizeof(T));
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix(const Matrix<T, 3, 3>& m)
    requires(p == 2 && q == 2)
{
    mElements[0] = m.data()[0];
    mElements[1] = m.data()[1];
    mElements[2] = m.data()[3];
    mElements[3] = m.data()[4];
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix(const Matrix<T, 4, 4>& m)
    requires(p == 2 && q == 2)
{
    mElements[0] = m.data()[0];
    mElements[1] = m.data()[1];
    mElements[2] = m.data()[4];
    mElements[3] = m.data()[5];
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix(const Matrix<T, 4, 4>& m)
    requires(p == 3 && q == 3)
{
    mElements[0] = m.data()[0];
    mElements[1] = m.data()[1];
    mElements[2] = m.data()[2];
    mElements[3] = m.data()[4];
    mElements[4] = m.data()[5];
    mElements[5] = m.data()[6];
    mElements[6] = m.data()[8];
    mElements[7] = m.data()[9];
    mElements[8] = m.data()[10];
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>::Matrix(const Matrix<T, p, q>& other) {
    ::memcpy(mElements, other.mElements, p * q * sizeof(T));
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator=(const Matrix<T, p, q>& other) {
    ::memcpy(mElements, other.mElements, p * q * sizeof(T));
    return *this;
}

template <std::floating_point T, u32 p, u32 q>
T Matrix<T, p, q>::operator()(const Index row, const Index col) const {
    return mElements[row * q + col];
}

template <std::floating_point T, u32 p, u32 q>
T& Matrix<T, p, q>::operator()(const Index row, const Index col) {
    return mElements[row * q + col];
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator+=(const Matrix<T, p, q>& rhs) {
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            mElements[row * q + col] += rhs.mElements[row * q + col];
    return *this;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator-=(const Matrix<T, p, q>& rhs) {
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            mElements[row * q + col] -= rhs.mElements[row * q + col];
    return *this;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator*=(const T& rhs) {
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            mElements[row * q + col] *= rhs;
    return *this;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator*=(const Matrix<T, p, q>& rhs)
    requires(p == q)
{
    return *this = *this * rhs;
}

template <std::floating_point T, u32 p, u32 q>
Matrix<T, p, q>& Matrix<T, p, q>::operator/=(const T& rhs) {
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            mElements[row * q + col] /= rhs;
    return *this;
}

template <std::floating_point T, u32 p, u32 q>
const T* Matrix<T, p, q>::data() const {
    return mElements;
}

template <std::floating_point T, u32 p, u32 q>
T* Matrix<T, p, q>::dataMutable() {
    return mElements;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator-(const Matrix<T, p, q>& rhs) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = -rhs(row, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator+(
    const Matrix<T, p, q>& lhs, const Matrix<T, p, q>& rhs
) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs(row, col) + rhs(row, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator-(
    const Matrix<T, p, q>& lhs, const Matrix<T, p, q>& rhs
) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs(row, col) - rhs(row, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator*(const Matrix<T, p, q>& lhs, const T rhs) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs(row, col) * rhs;
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator*(const T lhs, const Matrix<T, p, q>& rhs) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs * rhs(row, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator/(const Matrix<T, p, q>& lhs, const T rhs) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs(row, col) / rhs;
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, p, q> operator/(const T lhs, const Matrix<T, p, q>& rhs) {
    Matrix<T, p, q> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result(row, col) = lhs / rhs(row, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static Vector<T, p> operator*(
    const Matrix<T, p, q>& lhs, const Vector<T, q> rhs
) {
    Vector<T, p> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            result[row] += lhs(row, col) * rhs[col];
    return result;
}

template <std::floating_point T, u32 p, u32 q, u32 r>
static Matrix<T, p, r> operator*(
    const Matrix<T, p, q>& lhs, const Matrix<T, q, r>& rhs
) {
    Matrix<T, p, r> result;
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < r; ++col)
            for (Index k = 0; k < q; ++k)
                result(row, col) += lhs(row, k) * rhs(k, col);
    return result;
}

template <std::floating_point T, u32 p, u32 q>
static bool operator==(const Matrix<T, p, q>& lhs, const Matrix<T, p, q>& rhs) {
    for (Index row = 0; row < p; ++row)
        for (Index col = 0; col < q; ++col)
            if (lhs(row, col) != rhs(row, col))
                return false;
    return true;
}

template <std::floating_point T, u32 p, u32 q>
static bool operator!=(const Matrix<T, p, q>& lhs, const Matrix<T, p, q>& rhs) {
    return !(lhs == rhs);
}

template <std::floating_point T, u32 p, u32 q>
static Matrix<T, q, p> transpose(const Matrix<T, p, q>& value) {
    Matrix<T, q, p> result;
    for (Index row = 0; row < q; ++row)
        for (Index col = 0; col < p; ++col)
            result(row, col) = value(col, row);
    return result;
}

template <std::floating_point T, u32 p1, u32 q1, u32 p2, u32 q2>
static Matrix<T, p2, q2> embed_zero(
    const Matrix<T, p1, q1>& value, const Index x, const Index y
) {
    assertm(x < p1, "x not less than p1");
    assertm(p1 <= p2, "p1 not less than or equal to p2");
    assertm(y < q1, "y not less than q1");
    assertm(q1 <= q2, "q1 not less than or equal to q2");
    Matrix<T, p2, q2> result;
    for (Index row = x; row < p1; ++row)
        for (Index col = y; col < q1; ++col)
            result(row, col) = value(row, col);
    return result;
}

template <std::floating_point T, u32 dim1, u32 dim2>
static Matrix<T, dim2, dim2> embed_ident(
    const Matrix<T, dim1, dim1>& value, const Index x, const Index y
) {
    assertm(x < dim1, "x not less than dim1");
    assertm(y < dim1, "y not less than dim1");
    assertm(dim1 <= dim2, "dim1 not less than or equal to dim2");
    Matrix<T, dim2, dim2> result = Matrix<T, dim2, dim2>::ident();
    for (Index row = x; row < dim1; ++row)
        for (Index col = y; col < dim1; ++col)
            result(row, col) = value(row, col);
    return result;
}

template <std::floating_point T>
static Option<Matrix<T, 4, 4>> invert(const Matrix<T, 4, 4>& value) {
    // https://github.com/Starlink/mesa/blob/master/src/glu/sgi/libutil/project.c

    Matrix<T, 4, 4> inverse;

    const T* m = value.data();
    T* inv = inverse.dataMutable();

    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] +
             m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] +
             m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] +
             m[12] * m[7] * m[10];
    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] +
             m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] +
              m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] +
              m[12] * m[6] * m[9];
    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] +
             m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] +
             m[13] * m[3] * m[10];
    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] +
             m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] -
             m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] +
              m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] +
             m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] -
             m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] +
              m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] -
              m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] -
             m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] -
              m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

    const f64 det =
        m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == T(0))
        return std::nullopt;

    const f64 det_inv = T(1) / det;

    for (Index i = 0; i < 16; i++)
        inv[i] *= det_inv;

    return inverse;
}

template <std::floating_point T, u32 p, u32 q>
    requires FormatWritable<T>
struct FormatWriter<Matrix<T, p, q>> {
    static void write(const Matrix<T, p, q>& value, StringBuffer& sb) {
        sb.putSafe('[');
        for (Index i = 0; i < p - 1; ++i) {
            sb.putSafe('[');
            for (Index j = 0; j < q - 1; ++j)
                sb.appendFormat("{},", value(i, j));
            sb.appendFormat("{}],", value(i, q - 1));
        }
        sb.putSafe('[');
        for (Index j = 0; j < q - 1; ++j)
            sb.appendFormat("{},", value(p - 1, j));
        sb.appendFormat("{}]]", value(p - 1, q - 1));
    }
};
