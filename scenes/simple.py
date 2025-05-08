import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    SpecularMaterial,
    DielectricMaterial,
    RenderingMode,
    SceneNode,
    SphereNode,
)

mat_ground = LambertianMaterial(color=[0.8, 0.8, 0.0])
mat_center = LambertianMaterial(color=[0.1, 0.2, 0.5])
mat_left = DielectricMaterial(eta=1.5)
mat_bubble = DielectricMaterial(eta=1.0 / 1.5)
mat_right = SpecularMaterial(color=[0.8, 0.6, 0.2], phong=1.0)

root = SceneNode("root")

ground = SphereNode("ground", mat_ground)
ground.t(0.0, -100.5, -1.0)
ground.s(100.0)
root.add_child(ground)

center = SphereNode("center", mat_center)
center.t(0.0, 0.0, -1.2)
center.s(0.5)
root.add_child(center)

left = SphereNode("left", mat_left)
left.t(-1.0, 0.0, -1.0)
left.s(0.5)
root.add_child(left)

bubble = SphereNode("bubble", mat_bubble)
bubble.t(-1.0, 0.0, -1.0)
bubble.s(0.4)
root.add_child(bubble)

right = SphereNode("right", mat_right)
right.t(1.0, 0.0, -1.0)
right.s(0.5)
root.add_child(right)

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
config.samples_per_pixel = 100
config.trace_depth = 50

glacier.render("out.png", camera, root, config)
