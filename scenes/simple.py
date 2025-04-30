import glacier
from glacier import (
    LambertianMaterial,
    SphereNode,
    SceneNode,
    Camera
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

sphere = SphereNode("sphere", mat)
sphere.transform().t(0.0, 0.0, -1.0)
sphere.transform().s(0.5, 0.5, 0.5)
root.addChild(sphere)

ground = SphereNode("ground", mat)
ground.transform().t(0.0, -100.5, -1.0)
ground.transform().s(100.0, 100.0, 100.0)
root.addChild(ground)

camera = Camera(
    [0.0, 0.0, 0.0],
    [0.0, 0.0, -1.0],
    [0.0, 1.0, 0.0],
    90.0,
    400,
    225
)

glacier.render("out.png", camera, root)
