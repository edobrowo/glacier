import glacier
from glacier import (
    BezierPatchNode,
    Camera,
    Config,
    LambertianMaterial,
    SceneNode,
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

points = [
     [0.0, 0.0, 0.0],   [1.0, 0.0, 1.0],   [2.0, 0.0, -1.0],   [3.0, 0.0, 0.0],
     [0.0, 1.0, 1.0],   [1.0, 1.0, 2.0],   [2.0, 1.0, 0.0],    [3.0, 1.0, 1.0],
     [0.0, 2.0, -1.0],  [1.0, 2.0, 0.0],   [2.0, 2.0, 2.0],    [3.0, 2.0, -1.0],
     [0.0, 3.0, 0.0],   [1.0, 3.0, 1.0],   [2.0, 3.0, -1.0],   [3.0, 3.0, 0.0] 
]

bezier_patch = BezierPatchNode("bezier_patch", mat, control_points=points)
bezier_patch.t(-1.5, -0.5, 0.0)
bezier_patch.r(35.0, 0.0, 0.0)
bezier_patch.set_divisions(16, 16)
root.add_child(bezier_patch)

camera = Camera(
    look_from=[0.0, 0.0, -1.0],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.samples_per_pixel = 10

glacier.render("bezier_patch.png", camera, root, config)
