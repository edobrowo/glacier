import glacier
from glacier import (
    Camera,
    LambertianMaterial,
    QuadNode,
    SceneNode,
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

quad = QuadNode("quad", mat)
root.add_child(quad)

camera = Camera(
    look_from=[0.0, 0.0, -1.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

glacier.render("out.png", camera, root)
