import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    RenderingMode,
    SceneNode,
    SphereNode,
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

sphere = SphereNode("sphere", mat)
sphere.t(0.0, 0.0, -1.0)
sphere.s(0.5)
root.add_child(sphere)

ground = SphereNode("ground", mat)
ground.t(0.0, -100.5, -1.0)
ground.s(100.0)
root.add_child(ground)

camera = Camera(
    look_from=[0.0, 0.0, 0.0],
    look_at=[0.0, 0.0, -1.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.rendering_mode = RenderingMode.Full

glacier.render("out.png", camera, root, config)
