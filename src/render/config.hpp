#pragma once

#include "util/common.hpp"
#include "util/format.hpp"

enum class RenderingMode {
    Full = 0,
    NormalMap,
};

struct Config {
    RenderingMode renderingMode = RenderingMode::Full;
    u64 samplesPerPixel = 100;
    u64 traceDepth = 50;
};

template <>
struct FormatWriter<RenderingMode> {
    static void write(const RenderingMode& mode, StringBuffer& sb) {
        switch (mode) {
        case RenderingMode::Full:
            sb.append("Full", 4);
            break;
        case RenderingMode::NormalMap:
            sb.append("NormalMap", 9);
            break;
        default:
            unreachable;
        }
    }
};
