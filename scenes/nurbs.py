import glacier
from glacier import (
    NURBSNode,
    Camera,
    Config,
    LambertianMaterial,
    RenderingMode,
    SceneNode,
)

mat = LambertianMaterial(color=[0.5, 0.5, 0.5])

root = SceneNode("root")

control_points = [
    [-0.5, -0.5, 0], [0.5, -0.5, 1.0], [-0.5, 0.5, 1.0], [0.5, 0.5, 0.0]
]
control_weights = [1.0] * 4
u_knot_vector = [0.0, 0.0, 1.0, 1.0]
v_knot_vector = [0.0, 0.0, 1.0, 1.0]

nurbs = NURBSNode(
    "nurbs",
    mat,
    control_points=control_points,
    control_weights=control_weights,
    u_knot_vector=u_knot_vector,
    v_knot_vector=v_knot_vector
)
nurbs.r(90, 15, 0)
nurbs.t(0, 0.5, 0)
nurbs.set_divisions(8, 8)
root.add_child(nurbs)

camera = Camera(
    look_from=[0.0, 0.0, -1],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.samples_per_pixel = 10
config.rendering_mode = RenderingMode.NormalMap

glacier.render("out.png", camera, root, config)
