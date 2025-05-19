import glacier
from glacier import (
    Camera,
    Config,
    LambertianMaterial,
    PrimitiveKind,
    SceneNode,
    SphereNode,
)

mat_tl = LambertianMaterial(color=[1.0, 0.0, 0.0])
mat_tr = LambertianMaterial(color=[0.0, 1.0, 0.0])
mat_bl = LambertianMaterial(color=[0.0, 0.0, 1.0])
mat_br = LambertianMaterial(color=[1.0, 1.0, 0.0])

root = SceneNode("root")

tl = SphereNode("tl", mat_tl)
tl.t(0.6, 0.6, 0.0)
root.add_child(tl)

tr = SphereNode("tr", mat_tr)
tr.t(-0.6, 0.6, 0.0)
tr.set_primitive_kind(PrimitiveKind.Mesh)
tr.set_divisions(4, 4)
root.add_child(tr)

bl = SphereNode("bl", mat_bl)
bl.t(0.6, -0.6, 0.0)
bl.set_primitive_kind(PrimitiveKind.Mesh)
bl.set_divisions(8, 8)
root.add_child(bl)

br = SphereNode("br", mat_br)
br.t(-0.6, -0.6, 0.0)
br.set_primitive_kind(PrimitiveKind.Mesh)
br.set_divisions(16, 16)
root.add_child(br)

camera = Camera(
    look_from=[0.0, 0.0, -1.5],
    look_at=[0.0, 0.0, 0.0],
    up=[0.0, 1.0, 0.0],
    fov=90.0,
    nx=400,
    ny=225
)

config = Config()
config.samples_per_pixel = 10

glacier.render("sphere_geometry.png", camera, root, config)
