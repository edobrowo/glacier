import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    SceneNode,
    MeshNode
)

mat = LambertianMaterial(color=[0.7, 0.5, 0.5])

root = SceneNode("root")

mesh = MeshNode("mesh", mat, "examples/obj/cow.obj")
root.add_child(mesh)

camera = Camera(
    look_from=[0.0, 0.0, -10.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.samples_per_pixel = 10
config.trace_depth = 3

glacier.render("cow.png", camera, root, config)
