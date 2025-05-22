import glacier
from glacier import (
    Camera,
    LambertianMaterial,
    SceneNode,
    SphereNode,
    CuboidNode,
    TubeNode
)

red = LambertianMaterial(color=[1.0, 0.0, 0.0])
green = LambertianMaterial(color=[0.0, 1.0, 0.0])
blue = LambertianMaterial(color=[0.0, 0.0, 1.0])

root = SceneNode("root")
root.t(-3.0, -3.0, 0.0)

sphere = SphereNode("sphere", red)
sphere.t(1.5, 1.5, 0.0)
sphere.r(0.0, 0.0, -20.0)
root.add_child(sphere)

cuboid = CuboidNode("cuboid", green)
cuboid.t(1.5, 1.5, 0.0)
cuboid.r(45.0, 0.0, 0.0)
sphere.add_child(cuboid)

tube = TubeNode("tube", blue)
tube.t(1.5, 1.5, 0.0)
tube.r(0.0, 20.0, 0.0)
cuboid.add_child(tube)

camera = Camera(
    look_from=[0.0, 0.0, -3.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

glacier.render("hierarchy.png", camera, root)