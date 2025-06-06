import glacier
from glacier import (
    Camera,
    LambertianMaterial,
    SceneNode,
    TriangleNode,
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

tri = TriangleNode("tri", mat)
root.add_child(tri)

camera = Camera(
    look_from=[0.0, 0.0, -1.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

glacier.render("triangle.png", camera, root)
