import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    SpecularMaterial,
    MirrorSpecularMaterial,
    RenderingMode,
    SceneNode,
    SphereNode,
)

diffuse = LambertianMaterial(color=[0.5, 0.5, 0.5])
specular = SpecularMaterial(color=[0.9, 0.9, 0.9], phong=10)
mirror = MirrorSpecularMaterial(color=[1, 1, 1])

root = SceneNode("root")

s1 = SphereNode("s1", specular)
s1.t(-1.0, 0.0, -1.0)
s1.s(0.5)
root.add_child(s1)

s2 = SphereNode("s2", mirror)
s2.t(1.0, 0.0, -1.0)
s2.s(0.5)
root.add_child(s2)

ground = SphereNode("ground", diffuse)
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
