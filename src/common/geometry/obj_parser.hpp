#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "math/normal.hpp"
#include "math/point.hpp"
#include "math/vector.hpp"
#include "prelude.hpp"
#include "util/format.hpp"

namespace obj {

using View = std::string_view;

/// @brief Encapsulates a parsed value and an updated string view.
template <typename T>
struct ParseResult {
    T value;
    View rest;
};

enum class Keyword;

struct Polyline {
    std::vector<i64> indices;
};

struct FaceVertex {
    i64 position;
    Option<i64> texture;
    Option<i64> normal;

    bool operator==(const FaceVertex& other) const {
        return position == other.position && texture == other.texture &&
               normal == other.normal;
    }
};

struct Face {
    std::vector<FaceVertex> vertices;
};

}

namespace std {

template <>
struct hash<obj::FaceVertex> {
    std::size_t operator()(const obj::FaceVertex& v) const {
        return (
            (std::hash<i64>()(v.position) << 1) ^
            (std::hash<Option<i64>>()(v.texture) << 2) ^
            std::hash<Option<i64>>()(v.normal)
        );
    }
};

}

struct ObjObject {
    Option<std::string> name;

    // Vertex data.
    std::vector<Point3D> vertexPositions;
    std::vector<Point3D> vertexTexture;
    std::vector<Normal3D> vertexNormals;

    // Elements.
    std::vector<i64> points;
    std::vector<obj::Polyline> lines;
    std::vector<obj::Face> faces;
};

struct ObjData {
    std::vector<ObjObject> objects;
};

class ObjParser {
public:
    ObjParser() = default;
    ~ObjParser() = default;

    /// @brief Parses a Wavefront .obj object geometry file.
    ObjData parse(const std::string& obj) const;

private:
    /// @brief Parses a single line of a .obj file.
    /// @return The remaining view.
    obj::View parseLine(obj::View view, ObjData& data) const;

    /// @brief Parses a geometric vertex line from the beginning of the view.
    /// @returns A ParseResult containing the parsed vertex and the remaining
    /// view.
    obj::ParseResult<Point3D> parseVertex(obj::View view) const;

    /// @brief Parses a vertex texture coordinates line from the beginning of
    /// the view.
    /// @returns A ParseResult containing the parsed vertex texture coordinates
    /// and the remaining view.
    obj::ParseResult<Point3D> parseVertexTexture(obj::View view) const;

    /// @brief Parses a vertex normal line from the beginning of the view.
    /// @returns A ParseResult containing the parsed vertex normal and the
    /// remaining view.
    obj::ParseResult<Normal3D> parseVertexNormal(obj::View view) const;

    /// @brief Parses a point element line from the beginning of the view.
    /// @returns A ParseResult containing the parsed point index and the
    /// remaining view.
    obj::ParseResult<i64> parsePoint(obj::View view) const;

    /// @brief Parses a polyline element line from the beginning of the view.
    /// @returns A ParseResult containing the parsed polyline and the remaining
    /// view.
    obj::ParseResult<obj::Polyline> parsePolyline(obj::View view) const;

    /// @brief Parses a face element line from the beginning of the view.
    /// @returns A ParseResult containing the parsed face and the remaining
    /// view.
    obj::ParseResult<obj::Face> parseFace(obj::View view) const;

    /// @brief Tries to parses a face vertex from the beginning of the view.
    /// @returns An optional ParseResult containing the parsed face vertex and
    /// the remaining view.
    Option<obj::ParseResult<obj::FaceVertex>> tryParseFaceVertex(
        obj::View view
    ) const;

    /// @brief Parses an object name grouping line from the beginning of the
    /// view.
    /// @returns A ParseResult containing the object name and the remaining
    /// view.
    obj::ParseResult<obj::View> parseObjectName(obj::View view) const;

    /// @brief Parses a keyword from the beginning of the view.
    /// @returns A ParseResult containing the parsed keyword and the remaining
    /// view.
    obj::ParseResult<obj::Keyword> parseKeyword(obj::View view) const;

    /// @brief Parses a float from the beginning of the view.
    /// @returns A ParseResult containing the parsed float and the remaining
    /// view.
    obj::ParseResult<f64> parseFloat(obj::View view) const;

    /// @brief Tries to parse a float from the beginning of the view.
    /// @returns An optional ParseResult containing the parsed float and the
    /// remaining view.
    Option<obj::ParseResult<f64>> tryParseFloat(obj::View view) const;

    /// @brief Parses an index from the beginning of the view.
    /// @returns A ParseResult containing the parsed index and the remaining
    /// view.
    obj::ParseResult<i64> parseIndex(obj::View view) const;

    /// @brief Tries to parse an index from the beginning of the view.
    /// @returns An optional ParseResult containing the parsed index and the
    /// remaining view.
    Option<obj::ParseResult<i64>> tryParseIndex(obj::View view) const;

    /// @brief Skips commented characters in the view.
    /// @returns The view with commented characters removed.
    obj::View skipComment(obj::View view) const;

    /// @brief Skips leading whitespace characters in the view.
    /// @returns The view with leading whitespace removed.
    obj::View skipWhitespace(obj::View view) const;

    /// @brief Takes characters until a whitespace character is encountered.
    /// @returns A ParseResult containing the view of the non-whitespace
    /// characters and the remaining view.
    obj::ParseResult<obj::View> takeNonwhitespace(const obj::View view) const;

    /// @brief Finds the first whitespace character in the view.
    /// @returns The index of the whitespace character if found, otherwise
    /// std::nullopt.
    Option<Index> findWhitespace(const obj::View view) const;

    /// @brief Determines whether there is an escaped newline at the specified
    /// position.
    bool isEscapedNewline(const obj::View view, const Index pos) const;

    /// @brief Finds the first unescaped newline character in the view.
    /// @returns The index of the newline if found, otherwise std::nullopt.
    Option<Index> findUnescapedNewline(const obj::View view) const;

    /// @brief Converts 1-based indices to 0-based nonnegative indices.
    void convertIndices(ObjData& data) const;

    /// @brief Converts 1-based indices to 0-based nonnegative indices.
    void convertIndices(obj::Polyline& line, const i64 v_size) const;

    /// @brief Converts 1-based indices to 0-based nonnegative indices.
    void convertIndices(
        obj::Face& face, const i64 v_size, const i64 vt_size, const i64 vn_size
    ) const;
};

template <>
struct FormatWriter<obj::Polyline> {
    static void write(const obj::Polyline& line, StringBuffer& sb) {
        sb.putSafe('l');
        sb.putSafe(' ');
        for (Index i = 0; i < line.indices.size(); ++i) {
            sb.appendFormat("{}", line.indices[i]);
            if (i < line.indices.size() - 1)
                sb.putSafe(' ');
        }
    }
};

template <>
struct FormatWriter<obj::Face> {
    static void write(const obj::Face& face, StringBuffer& sb) {
        sb.putSafe('f');
        sb.putSafe(' ');
        for (Index i = 0; i < face.vertices.size(); ++i) {
            const obj::FaceVertex& v = face.vertices[i];

            sb.appendFormat("{}", v.position + 1);

            if (v.texture) {
                sb.putSafe('/');
                sb.appendFormat("{}", *v.texture + 1);
            }

            if (v.normal) {
                if (!v.texture)
                    sb.putSafe('/');
                sb.putSafe('/');
                sb.appendFormat("{}", *v.normal + 1);
            }

            if (i < face.vertices.size() - 1)
                sb.putSafe(' ');
        }
    }
};

template <>
struct FormatWriter<ObjObject> {
    static void write(const ObjObject& obj, StringBuffer& sb) {
        if (obj.name)
            sb.appendFormat("o {}\n\n", *obj.name);

        for (const Point3D& v : obj.vertexPositions)
            sb.appendFormat("v {} {} {}\n", v.x, v.y, v.z);

        if (!obj.vertexPositions.empty())
            sb.putSafe('\n');

        for (const Point3D& vt : obj.vertexTexture)
            sb.appendFormat("vt {} {} {}\n", vt.x, vt.y, vt.z);
        if (!obj.vertexTexture.empty())
            sb.putSafe('\n');

        for (const Normal3D& vn : obj.vertexNormals)
            sb.appendFormat("vn {} {} {}\n", vn.x, vn.y, vn.z);
        if (!obj.vertexNormals.empty())
            sb.putSafe('\n');

        for (const i64 p : obj.points)
            sb.appendFormat("p {}\n", p);
        if (!obj.points.empty())
            sb.putSafe('\n');

        for (const obj::Polyline& l : obj.lines)
            sb.appendFormat("{}\n", l);
        if (!obj.lines.empty())
            sb.putSafe('\n');

        for (const obj::Face& f : obj.faces)
            sb.appendFormat("{}\n", f);
    }
};

template <>
struct FormatWriter<ObjData> {
    static void write(const ObjData& data, StringBuffer& sb) {
        for (const ObjObject& obj : data.objects)
            sb.appendFormat("{}\n", obj);
    }
};
