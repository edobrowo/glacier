import glacier
from glacier import (
    Camera,
    LambertianMaterial,
    EmissiveMaterial,
    SceneNode,
    SphereNode,
)

mat_center = LambertianMaterial(color=[0.5, 0.5, 0.5])
mat_light = EmissiveMaterial(color=[4.0, 4.0, 4.0])

root = SceneNode("root")

center = SphereNode("center", mat_center)
center.t(0.0, -0.5, -1.2)
center.s(0.4)
root.add_child(center)

light = SphereNode("light", mat_light)
light.t(0.0, 0.5, -1.2)
light.s(0.4)
root.add_child(light)

camera = Camera(
    look_from=[0.0, 0.0, 0.0],
    look_at=[0.0, 0.0, -1.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

glacier.render("out.png", camera, root)
