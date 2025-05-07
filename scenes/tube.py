import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    SceneNode,
    TubeNode
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

tube = TubeNode("tube", mat)
tube.r(0, 50, 0)
root.add_child(tube)

camera = Camera(
    look_from=[0.0, 0.0, -2.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.samples_per_pixel = 5
config.trace_depth = 3

glacier.render("out.png", camera, root, config)
