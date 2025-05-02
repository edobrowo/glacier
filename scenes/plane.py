import glacier
from glacier import (
    Camera,
    LambertianMaterial,
    SceneNode,
    QuadNode,
)

mat_plane = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

plane = QuadNode("plane", mat_plane)
plane.t(0.0, 0.0, -1.0)
plane.r(90, 0.0, 0.0)
root.add_child(plane)

camera = Camera(
    look_from=[0.0, 0.0, 0.0],
    look_at=[0.0, 0.0, -1.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

glacier.render("out.png", camera, root)
