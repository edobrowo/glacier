#include "render/pathtracer.hpp"

#include <thread>
#include <vector>

#include "common/util/log.hpp"
#include "render/material/emissive.hpp"
#include "render/primitive_builder.hpp"
#include "scene/nodes/geometry_node.hpp"

namespace {

void buildPrimitivesRecursive(SceneNodePtr& node) {
    PrimitivePtr prim = nullptr;

    if (auto cuboid = dynamic_cast<CuboidNode*>(node.get())) {
        prim = PrimitiveBuilder<CuboidNode>::build(*cuboid);
        prim->setMaterial(cuboid->material());
    } else if (auto disk = dynamic_cast<DiskNode*>(node.get())) {
        prim = PrimitiveBuilder<DiskNode>::build(*disk);
        prim->setMaterial(disk->material());
    } else if (auto quad = dynamic_cast<QuadNode*>(node.get())) {
        prim = PrimitiveBuilder<QuadNode>::build(*quad);
        prim->setMaterial(quad->material());
    } else if (auto sphere = dynamic_cast<SphereNode*>(node.get())) {
        prim = PrimitiveBuilder<SphereNode>::build(*sphere);
        prim->setMaterial(sphere->material());
    } else if (auto tri = dynamic_cast<TriangleNode*>(node.get())) {
        prim = PrimitiveBuilder<TriangleNode>::build(*tri);
        prim->setMaterial(tri->material());
    } else if (auto tube = dynamic_cast<TubeNode*>(node.get())) {
        prim = PrimitiveBuilder<TubeNode>::build(*tube);
        prim->setMaterial(tube->material());
    } else if (auto geo = dynamic_cast<GeometryNode*>(node.get())) {
        prim = PrimitiveBuilder<GeometryNode>::build(*geo);
        prim->setMaterial(geo->material());
    }

    if (auto geo = dynamic_cast<GeometryNode*>(node.get()))
        geo->setPrimitive(std::move(prim));

    for (SceneNodePtr& child : node->childrenMutable())
        buildPrimitivesRecursive(child);
}

}

Pathtracer::Pathtracer(SceneGraph& scene, const Camera& camera)
    : mScene(scene), mCamera(camera) {
    buildPrimitivesRecursive(mScene.rootMutable());
    // mScene.buildPrimitives();
}

Image Pathtracer::render() const {
    Image image(mCamera.nx(), mCamera.ny());

    const Size thread_count = 8;
    Log::i("Hardware concurrency = {}", thread_count);

    std::vector<std::thread> threads;

    const f64 color_scale = 1.0 / static_cast<f64>(config.samplesPerPixel);

    auto render_rows = [&](Index row_start, Index row_end) {
        for (Index py = row_start; py < row_end; ++py) {
            for (Index px = 0; px < mCamera.nx(); ++px) {
                Vector3D color = Vector3D::zero();

                if (config.samplingKind == SamplingKind::Center) {
                    const Ray ray = generate(px, py);
                    color = shadeRecursive(ray, 1);
                } else {
                    for (Index sample = 0; sample < config.samplesPerPixel;
                         ++sample) {
                        const Ray ray = generate(px, py);

                        color += shadeRecursive(ray, 1);
                    }

                    color *= color_scale;
                }

                image.set(px, py, color);
            }
        }
    };

    const Size rows_per_thread = mCamera.ny() / thread_count;

    for (Index i = 0; i < thread_count; ++i) {
        const Index row_start = i * rows_per_thread;
        const Index row_end = (i == thread_count - 1)
                                  ? mCamera.ny()
                                  : row_start + rows_per_thread;

        threads.emplace_back(render_rows, row_start, row_end);
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    return image;
}

Ray Pathtracer::generate(const Index px, const Index py) const {
    const Point3D origin = mCamera.origin();

    Point3D point_sample;

    switch (config.samplingKind) {
    case SamplingKind::Center:
        point_sample = mCamera.p(px, py);
        break;
    case SamplingKind::UniformRandom:
        point_sample = mCamera.sample(px, py);
        break;
    default:
        unreachable;
    }

    const Vector3D direction = (point_sample - origin).normalize();

    return Ray(origin, direction);
}

Vector3D Pathtracer::shadeRecursive(const Ray& ray, const Size depth) const {
    if (depth >= config.traceDepth)
        return Vector3D::zero();

    if (const Option<SurfaceInteraction> option = intersect(ray)) {
        const MaterialPtr mat = option->mat;

        const Option<ScatterRecord> record = mat->scatter(ray, *option);

        switch (config.renderingMode) {
        case RenderingMode::Full:
            if (record) {
                return record->color *
                       shadeRecursive(record->scattered, depth + 1);
            } else {
                if (mat->kind() == Material::Kind::Emissive)
                    return static_cast<Emissive*>(mat.get())->emitted();
                else
                    return Vector3D::zero();
            }
            break;
        case RenderingMode::NormalMap:
            return 0.5 * (option->n.normalize() + Vector3D::one());
            break;
        default:
            unreachable;
        }
    }

    return background(ray);
}

Option<SurfaceInteraction> Pathtracer::intersect(const Ray& ray) const {
    return intersectRecursive(
        mScene.root(), ray, Interval(0.001, math::infinity<f64>())
    );
}

Option<SurfaceInteraction> Pathtracer::intersectRecursive(
    const SceneNodePtr& node, const Ray& ray, const Interval& bounds
) const {
    // Current closest intersection and interval.
    Option<SurfaceInteraction> closest = std::nullopt;
    Interval closest_bounds(bounds);

    const Transform& transform = node->transform().transform();
    const Transform& inverse = invert(transform);

    // On "the way down", transform the ray with the current node's inverse
    // transformation.
    const Ray inverse_ray = inverse(ray);

    // Compute the intersect with the current node if it contains a primitive.
    if (node->kind() == SceneNode::Kind::Geometry) {
        const GeometryNode* geo = static_cast<GeometryNode*>(node.get());
        if (const Option<SurfaceInteraction> interaction =
                geo->primitive()->intersect(inverse_ray, bounds)) {
            closest = interaction;
            closest->mat = geo->material();
            closest_bounds.max = std::min(closest->t, closest_bounds.max);
        }
    }

    // Recursively compute the intersection over all children nodes, and
    // determine the minimum intersection.
    for (const SceneNodePtr& child : node->children()) {
        if (const Option<SurfaceInteraction> interaction =
                intersectRecursive(child, inverse_ray, closest_bounds)) {
            if (!closest || interaction->t < closest->t) {
                closest = interaction;
                closest_bounds.max = interaction->t;
            }
        }
    }

    // On "the way up", create a new ray where the origin is transformed with
    // the current node's transformation, and the normal is transformed with
    // the upper 3x3 of the transpose of the inverse of the current node's
    // transformation.
    if (closest) {
        closest->p = transform(closest->p);
        closest->n = transform(closest->n).normalize();
    }

    return closest;
}

Vector3D Pathtracer::background(const Ray& ray) const {
    const Vector3D direction = ray.direction.normalize();
    const f64 a = 0.5 * (direction.y + 1.0);
    return (1.0 - a) * Vector3D::uniform(1.0) + a * Vector3D(0.5, 0.7, 1.0);
}
