import bpy
import os
import math
from mathutils import Matrix

def euler_to_axis_angle(rotation_euler):
    # Convert Euler angles to rotation matrix
    rotation_matrix = Matrix.Rotation(rotation_euler[2], 4, 'Z') @ Matrix.Rotation(rotation_euler[1], 4, 'Y') @ Matrix.Rotation(rotation_euler[0], 4, 'X')

    # Get axis-angle representation from rotation matrix
    axis, angle = rotation_matrix.to_quaternion().to_axis_angle()

    # Convert the axis to raylib coordinate system
    axis = (axis.x, axis.z, -axis.y)

    return axis, angle


def export_mesh_objects_to_glb(output_directory):
    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    # Iterate through all objects in the scene
    for obj in bpy.context.scene.objects:
        # Check if the object is a mesh
        if obj.type == 'MESH':
            # Make the current object the active object
            bpy.context.view_layer.objects.active = obj

            # Select only the current object
            bpy.ops.object.select_all(action='DESELECT')
            obj.select_set(True)

            # Export the selected object to .glb file
            output_filename = os.path.join(output_directory, f"{obj.name}.glb")
            bpy.ops.export_scene.gltf(filepath=output_filename, export_format='GLB', use_selection=True)

            # Deselect the object after export
            obj.select_set(False)

    print("Export complete.")


def create_scene_info_file(output_directory):
    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)
    
    # Information to store about each object
    object_info = []
    # Parent-child relationships
    parent_child_info = {}

    # Iterate through all objects in the scene
    for obj in bpy.context.scene.objects:
        # Check if the object is a mesh
        if obj.type == 'MESH':
            # Store the global transformation matrix
            global_matrix = obj.matrix_world

            # Apply the global transformation to get global position, rotation, and scale
            global_location, global_rotation, global_scale = global_matrix.decompose()

            # Swap Y and Z locations for change to raylib coords
            location_x, location_y, location_z = global_location
            swapped_location = (location_x, location_z, location_y * -1)
            
            # Convert euler to axis angle
            axis, angle = euler_to_axis_angle(obj.rotation_euler)

            # Append object information to the list
            object_info.append({
                'name': obj.name,
                'location': swapped_location,
                'rotation_axis': axis,
                'rotation_angle': angle,
                'scale': global_scale[:]
            })
            
            # Check if the object has a parent
            if obj.parent:
                parent_name = obj.parent.name
                child_name = obj.name
                parent_child_info[child_name] = parent_name

    # Write object information to a text file
    scene_info_filename = os.path.join(output_directory, "scene.txt")
    with open(scene_info_filename, 'w') as file:
        for info in object_info:
            file.write(f"Object  {info['name']}\n")
            file.write(f"Location {info['location']}\n")
            file.write(f"RotationAxis {info['rotation_axis']}\n")
            file.write(f"RotationAngle {info['rotation_angle']}\n")
            file.write(f"Scale {info['scale']}\n")
            
            # Check if the object has a parent and record the relationship
            if info['name'] in parent_child_info:
                file.write(f"Parent {parent_child_info[info['name']]}\n")
            else:
                file.write (f"Parent root\n")
            
            file.write(f"End\n")
            file.write("\n")

    print("Scene information file created.")

# Bake the objects' materials to their textures.

# Set the objects' materials to their new texture versions

# Export the Meshes to their GLB files at the specified directory.
output_directory = os.path.dirname(bpy.data.filepath)
export_mesh_objects_to_glb(output_directory)

# Set the objects' materials back to their procedural versions

# Create the scene.txt file with information about each object's location, rotation, scale, parent-child relationships, and other information
# For parsing into the game engine when loading the scene
create_scene_info_file(output_directory)
