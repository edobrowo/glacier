#pragma once

#include "util/common.hpp"
#include "util/format.hpp"

enum class RenderingMode {
    Full = 0,
    NormalMap,
};

enum class SamplingKind {
    MonoStratified = 0,
    RandomUniform,
};

struct Config {
    RenderingMode renderingMode = RenderingMode::Full;
    SamplingKind samplingKind = SamplingKind::RandomUniform;
    u64 samplesPerPixel = 100;
    u64 traceDepth = 50;
};

template <>
struct FormatWriter<SamplingKind> {
    static void write(const SamplingKind& kind, StringBuffer& sb) {
        switch (kind) {
        case SamplingKind::MonoStratified:
            sb.append("MonoStratified");
            break;
        case SamplingKind::RandomUniform:
            sb.append("RandomUniform");
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
