#pragma once

#include "common/prelude.hpp"
#include "common/util/format.hpp"

enum class RenderingMode {
    Full = 0,
    NormalMap,
};

enum class SamplingKind {
    Center = 0,
    UniformRandom,
};

struct Config {
    RenderingMode renderingMode = RenderingMode::Full;
    SamplingKind samplingKind = SamplingKind::UniformRandom;
    u64 samplesPerPixel = 100;
    u64 traceDepth = 50;
};

template <>
struct FormatWriter<SamplingKind> {
    static void write(const SamplingKind& kind, StringBuffer& sb) {
        switch (kind) {
        case SamplingKind::Center:
            sb.append("Center");
            break;
        case SamplingKind::UniformRandom:
            sb.append("UniformRandom");
            break;
        default:
            unreachable;
        }
    }
};

template <>
struct FormatWriter<RenderingMode> {
    static void write(const RenderingMode& mode, StringBuffer& sb) {
        switch (mode) {
        case RenderingMode::Full:
            sb.append("Full");
            break;
        case RenderingMode::NormalMap:
            sb.append("NormalMap");
            break;
        default:
            unreachable;
        }
    }
};
