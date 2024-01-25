import bpy, os, sys
from bpy_extras.io_utils import ExportHelper
from array import array
import struct

bl_info = {
	"name": "lemon",
	"blender": (2, 80, 0),
	"category": "Import-Export",
	"location": "File > Import-Export",
}

class Lemon(bpy.types.Operator, ExportHelper):
	bl_idname = "file.lemon"
	bl_label = "Lemon Export"

	filename_ext = '.lm'
	filter_glob: bpy.props.StringProperty(
		default='*.lm',
		options={'HIDDEN'}
	)

	def execute(self, context):
		with open(self.filepath, 'wb') as o:
			sys.stdout = o
			d = bpy.context.object.data

			o.write(struct.pack('i',len(d.vertices)))
			o.write(struct.pack('i',len(d.polygons)))

			vb = []

			for f in d.polygons:
				for v in f.vertices:
					vert = []
					for i in d.vertices[v].co:
						vert.append(i)
					for i in d.uv_layers.active.data[v].uv:
						vert.append(i)
					for i in d.vertices[v].normal:
						vert.append(i)
					vb.append(vert)

			vert = [float] * 8
			va = [vert] * len(d.vertices)
			ind = [int] * 3 * len(d.polygons)

			i = 0
			for f in d.polygons:
				for v in f.vertices:
					ind[i] = v
					va[v] = vb[i]
					i += 1
			
			for v in va:
				vertbytes = struct.pack('f'*len(v), *v)
				o.write(vertbytes)

			o.write(struct.pack('i'*len(ind),*ind))
		return {'FINISHED'}

def menu_func(self, context):
	self.layout.operator(Lemon.bl_idname)

def register():
	bpy.utils.register_class(Lemon)
	bpy.types.TOPBAR_MT_file_export.append(menu_func)

def unregister():
	bpy.utils.unregister_class(Lemon)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func)

if __name__ == "__main__":
	register()

