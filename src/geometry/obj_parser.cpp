#include "obj_parser.hpp"

#include <map>

#include "util/common.hpp"
#include "util/format.hpp"
#include "util/log.hpp"

constexpr const char* cWhitespaceAll = " \f\n\r\t\v";
constexpr const char* cWhitespaceNoNewline = " \f\r\t\v";

namespace obj {

/// @brief OBJ keyword.
enum class Keyword {
    // Vertex data.
    VertexGeometric,
    VertexTexture,
    VertexNormal,
    VertexParameter,  // TODO:

    // Free-form curve or surface.
    Degree,              // TODO:
    BasisMatrix,         // TODO:
    StepSize,            // TODO:
    CurveOrSurfaceType,  // TODO:

    // Elements.
    Point,
    Line,
    Face,
    Curve,    // TODO:
    Curve2D,  // TODO:
    Surface,  // TODO:

    // Free-form curve or surface body statements.
    Parameter,          // TODO:
    OuterTrimmingLoop,  // TODO:
    InnerTrimmingLoop,  // TODO:
    SpecialCurve,       // TODO:
    SpecialPoint,       // TODO:
    EndStatement,       // TODO:

    // Connectivity between free-form surfaces.
    Connect,  // TODO:

    // Grouping.
    GroupName,       // TODO:
    SmoothingGroup,  // TODO:
    MergingGroup,    // TODO:
    ObjectName,

    // Display and render attributes.
    BevelInterpolation,             // TODO:
    ColorInterpolation,             // TODO:
    DissolveInterpolation,          // TODO:
    LevelOfDetail,                  // TODO:
    MaterialName,                   // TODO:
    MaterialLibrary,                // TODO:
    ShadowCasting,                  // TODO:
    RayTracing,                     // TODO:
    CurveApproximationTechnique,    // TODO:
    SurfaceApproximationTechnique,  // TODO:
};

std::map<std::string, Keyword> keywordStrings = {
    // Vertex data.
    {"v", Keyword::VertexGeometric},
    {"vt", Keyword::VertexTexture},
    {"vn", Keyword::VertexNormal},
    {"vp", Keyword::VertexParameter},

    // Free-form curve or surface.
    {"deg", Keyword::Degree},
    {"bmat", Keyword::BasisMatrix},
    {"step", Keyword::StepSize},
    {"cstype", Keyword::CurveOrSurfaceType},

    // Elements.
    {"p", Keyword::Point},
    {"l", Keyword::Line},
    {"f", Keyword::Face},
    {"curv", Keyword::Curve},
    {"curv2", Keyword::Curve2D},
    {"surf", Keyword::Surface},

    // Free-form curve or surface body statements.
    {"parm", Keyword::Parameter},
    {"trim", Keyword::OuterTrimmingLoop},
    {"hole", Keyword::InnerTrimmingLoop},
    {"scrv", Keyword::SpecialCurve},
    {"sp", Keyword::SpecialPoint},
    {"end", Keyword::EndStatement},

    // Connectivity between free-form surfaces.
    {"con", Keyword::Connect},

    // Grouping.
    {"g", Keyword::GroupName},
    {"s", Keyword::SmoothingGroup},
    {"mg", Keyword::MergingGroup},
    {"o", Keyword::ObjectName},

    // Display and render attributes.
    {"bevel", Keyword::BevelInterpolation},
    {"c_interp", Keyword::ColorInterpolation},
    {"d_interp", Keyword::DissolveInterpolation},
    {"lod", Keyword::LevelOfDetail},
    {"usemtl", Keyword::MaterialName},
    {"mtllib", Keyword::MaterialLibrary},
    {"shadow_obj", Keyword::ShadowCasting},
    {"trace_obj", Keyword::RayTracing},
    {"ctech", Keyword::CurveApproximationTechnique},
    {"stech", Keyword::SurfaceApproximationTechnique},
};

}

using namespace obj;

ObjData ObjParser::parse(const std::string& obj) const {
    View view = obj;
    ObjData data{};

    while (!view.empty())
        view = parseLine(view, data);

    // Post-processing step. Converts all indices to 0-based, nonnegative
    // values.
    convertIndices(data);

    return data;
}

View ObjParser::parseLine(View view, ObjData& data) const {
    // Skip any leading whitespace.
    view = skipWhitespace(view);

    // Check for commented line.
    if (view.starts_with('#'))
        return skipComment(view);

    // Check for empty line.
    if (view.starts_with("\n"))
        return view.substr(1);

    // Parse the keyword.
    const ParseResult<Keyword> result = parseKeyword(view);
    view = result.rest;

    // Case when the file contains a single unnamed object.
    if (data.objects.empty() && result.value != Keyword::ObjectName) {
        data.objects.emplace_back();
    }

    ObjObject& obj = data.objects.back();

    switch (result.value) {
    // Vertex data.
    case Keyword::VertexGeometric: {
        const ParseResult<Point3D> result = parseVertex(view);
        obj.vertexPositions.push_back(result.value);
        view = result.rest;
        break;
    }
    case Keyword::VertexTexture: {
        const ParseResult<Point3D> result = parseVertexTexture(view);
        obj.vertexTexture.push_back(result.value);
        view = result.rest;
        break;
    }
    case Keyword::VertexNormal: {
        const ParseResult<Vector3D> result = parseVertexNormal(view);
        obj.vertexNormals.push_back(result.value);
        view = result.rest;
        break;
    }

    // Elements.
    case Keyword::Point: {
        const ParseResult<i64> result = parsePoint(view);
        obj.points.push_back(result.value);
        view = result.rest;
        break;
    }
    case Keyword::Line: {
        const ParseResult<Polyline> result = parsePolyline(view);
        obj.lines.push_back(result.value);
        view = result.rest;
        break;
    }
    case Keyword::Face: {
        const ParseResult<Face> result = parseFace(view);
        obj.faces.push_back(result.value);
        view = result.rest;
        break;
    }

    // Grouping.
    case Keyword::ObjectName: {
        const ParseResult<View> result = parseObjectName(view);
        data.objects.emplace_back();
        data.objects.back().name = result.value;
        view = result.rest;
        break;
    }

    default:
        unimplemented;
    }

    // Skip any trailing whitespace.
    view = skipWhitespace(view);

    // Skip the newline.
    if (!view.empty())
        view = view.substr(1);

    return view;
}

ParseResult<Point3D> ObjParser::parseVertex(View view) const {
    const ParseResult<f64> c1 = parseFloat(view);
    const ParseResult<f64> c2 = parseFloat(c1.rest);
    const ParseResult<f64> c3 = parseFloat(c2.rest);

    Point3D p(c1.value, c2.value, c3.value);
    view = c3.rest;

    // Try to parse a fourth component.
    if (const Option<ParseResult<f64>> c4 = tryParseFloat(view)) {
        view = c4->rest;
        p = Point3D(p.pos() / c4->value);
    }

    return {p, view};
}

ParseResult<Point3D> ObjParser::parseVertexTexture(View view) const {
    const ParseResult<f64> c1 = parseFloat(view);

    Point3D p(c1.value, 0.0, 0.0);
    view = c1.rest;

    // Try to parse a second component.
    if (const Option<ParseResult<f64>> c2 = tryParseFloat(view)) {
        view = c2->rest;
        p.y = c2->value;
    } else {
        return {p, view};
    }

    // Try to parse a third component.
    if (const Option<ParseResult<f64>> c3 = tryParseFloat(view)) {
        view = c3->rest;
        p.z = c3->value;
    }

    return {p, view};
}

ParseResult<Vector3D> ObjParser::parseVertexNormal(View view) const {
    const ParseResult<f64> c1 = parseFloat(view);
    const ParseResult<f64> c2 = parseFloat(c1.rest);
    const ParseResult<f64> c3 = parseFloat(c2.rest);

    const Vector3D p(c1.value, c2.value, c3.value);
    view = c3.rest;

    return {p, view};
}

ParseResult<i64> ObjParser::parsePoint(View view) const {
    const ParseResult<i64> v = parseIndex(view);
    return {v.value, v.rest};
}

ParseResult<Polyline> ObjParser::parsePolyline(View view) const {
    Polyline line;
    while (const Option<ParseResult<i64>> v = tryParseIndex(view)) {
        line.indices.push_back(v->value - 1);
        view = v->rest;
    }
    return {line, view};
}

ParseResult<Face> ObjParser::parseFace(View view) const {
    Face face;
    while (const Option<ParseResult<FaceVertex>> v = tryParseFaceVertex(view)) {
        face.vertices.push_back(v->value);
        view = v->rest;
    }
    return {face, view};
}

Option<ParseResult<FaceVertex>> ObjParser::tryParseFaceVertex(View view) const {
    view = skipWhitespace(view);

    const Option<ParseResult<i64>> vp = tryParseIndex(view);
    if (!vp)
        return std::nullopt;

    FaceVertex v;
    v.position = vp->value;
    view = vp->rest;

    if (!view.empty() && view[0] == '/') {
        view = view.substr(1);

        if (!view.empty() && view[0] == '/') {
            // Position//Normal.
            view = view.substr(1);
            const ParseResult<i64> vn = parseIndex(view);
            v.normal = vn.value;
            view = vn.rest;

        } else {
            // Position/Texture.
            const ParseResult<i64> vt = parseIndex(view);
            v.texture = vt.value;
            view = vt.rest;

            if (!view.empty() && view[0] == '/') {
                // Position/Texture/Normal.
                view = view.substr(1);
                const ParseResult<i64> vn = parseIndex(view);
                v.normal = vn.value;
                view = vn.rest;
            }
        }
    }

    return Option<ParseResult<FaceVertex>>({v, view});
}

ParseResult<View> ObjParser::parseObjectName(View view) const {
    view = skipWhitespace(view);
    return takeNonwhitespace(view);
}

ParseResult<Keyword> ObjParser::parseKeyword(View view) const {
    const ParseResult<View> result = takeNonwhitespace(view);
    const std::string key(result.value);

    if (keywordStrings.find(key) != keywordStrings.end()) {
        return {keywordStrings[key], result.rest};
    } else {
        throw std::runtime_error(format("invalid keyword: {}", key));
    }
}

ParseResult<f64> ObjParser::parseFloat(View view) const {
    view = skipWhitespace(view);

    const char* start = view.data();
    char* end = nullptr;

    const f64 value = std::strtod(start, &end);

    if (end != start) {
        const Index length = static_cast<Index>(end - start);
        return {value, view.substr(length)};
    }

    throw std::runtime_error("failed to parse float");
}

Option<ParseResult<f64>> ObjParser::tryParseFloat(View view) const {
    if (view.empty())
        return std::nullopt;

    view = skipWhitespace(view);

    const char* start = view.data();
    char* end = nullptr;

    const f64 value = std::strtod(start, &end);

    if (end != start) {
        const Index length = static_cast<Index>(end - start);
        return Option<ParseResult<f64>>({value, view.substr(length)});
    }

    return std::nullopt;
}

ParseResult<i64> ObjParser::parseIndex(View view) const {
    view = skipWhitespace(view);

    const char* start = view.data();
    char* end = nullptr;

    const i64 value = std::strtoll(start, &end, 10);

    if (end != start) {
        const Index length = static_cast<Index>(end - start);
        return {value, view.substr(length)};
    }

    throw std::runtime_error("failed to parse integral index");
}

Option<ParseResult<i64>> ObjParser::tryParseIndex(View view) const {
    if (view.empty())
        return std::nullopt;

    view = skipWhitespace(view);

    const char* start = view.data();
    char* end = nullptr;

    const i64 value = std::strtoll(start, &end, 10);

    if (end != start) {
        const Index length = static_cast<Index>(end - start);
        return Option<ParseResult<i64>>({value, view.substr(length)});
    }

    return std::nullopt;
}

View ObjParser::skipComment(View view) const {
    if (const Option<Index> pos = findUnescapedNewline(view))
        return view.substr(*pos + 1);
    else
        return View{};
}

View ObjParser::skipWhitespace(View view) const {
    while (true) {
        const Index pos = view.find_first_not_of(cWhitespaceNoNewline);

        if (pos == View::npos)
            return {};

        view = view.substr(pos);

        if (isEscapedNewline(view, 0)) {
            view = view.substr(1);
            continue;
        }

        break;
    }

    return view;
}

ParseResult<View> ObjParser::takeNonwhitespace(const View view) const {
    const Index pos = view.find_first_of(cWhitespaceAll);
    return {view.substr(0, pos), view.substr(pos)};
}

Option<Index> ObjParser::findWhitespace(const View view) const {
    const Index pos = view.find_first_of(cWhitespaceNoNewline);
    if (pos != View::npos)
        return pos;
    else
        return std::nullopt;
}

bool ObjParser::isEscapedNewline(const View view, const Index pos) const {
    return (pos + 1 < view.size()) && (view[pos] == '\\') &&
           (view[pos + 1] == '\n');
}

Option<Index> ObjParser::findUnescapedNewline(const View view) const {
    Index pos = 0;
    while ((pos = view.find('\n')) != View::npos) {
        if (pos == 0 || view[pos - 1] != '\\')
            return pos;
        ++pos;
    }
    return std::nullopt;
}

void ObjParser::convertIndices(ObjData& data) const {
    for (ObjObject& obj : data.objects) {
        const i64 v_size = obj.vertexPositions.size();
        const i64 vt_size = obj.vertexTexture.size();
        const i64 vn_size = obj.vertexNormals.size();

        for (i64& p : obj.points)
            p = (p > 0) ? p - 1 : v_size + p;

        for (Polyline& line : obj.lines)
            convertIndices(line, v_size);

        for (Face& face : obj.faces)
            convertIndices(face, v_size, vt_size, vn_size);
    }
}

void ObjParser::convertIndices(obj::Polyline& line, const i64 v_size) const {
    for (i64& i : line.indices)
        i = (i > 0) ? i - 1 : v_size + i;
}

void ObjParser::convertIndices(obj::Face& face,
                               const i64 v_size,
                               const i64 vt_size,
                               const i64 vn_size) const {
    for (FaceVertex& v : face.vertices) {
        i64& vp = v.position;
        Option<i64>& vt = v.texture;
        Option<i64>& vn = v.normal;

        vp = (vp > 0) ? vp - 1 : v_size + vp;
        if (vt)
            vt = (*vt > 0) ? *vt - 1 : v_size + *vt;
        if (vn)
            vn = (*vn > 0) ? *vn - 1 : v_size + *vn;
    }
}
