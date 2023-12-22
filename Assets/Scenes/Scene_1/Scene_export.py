import bpy
import os

print("running")

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

    # Iterate through all objects in the scene
    for obj in bpy.context.scene.objects:
        # Check if the object is a mesh
        if obj.type == 'MESH':
            # Append object information to the list
            object_info.append({
                'name': obj.name,
                'location': obj.location[:],
                'rotation_euler': obj.rotation_euler[:],
                'scale': obj.scale[:]
            })
    
    # Write object information to a text file
    scene_info_filename = os.path.join(output_directory, "scene.txt")
    with open(scene_info_filename, 'w') as file:
        for info in object_info:
            file.write(f"Object: {info['name']}\n")
            file.write(f"  Location: {info['location']}\n")
            file.write(f"  Rotation: {info['rotation_euler']}\n")
            file.write(f"  Scale: {info['scale']}\n\n")

    print("Scene information file created.")

# Bake the objects materials to their textures.

# Set the objects materials to their new texture versions

# Export the Meshes to their GLB files at the specified directory.
output_directory = "C:/Users/leons/Documents/projects/SparrowHawk/Assets/Scene_1"
export_mesh_objects_to_glb(output_directory)

# Set the objects materials back to their procedural versions

# Create the scene.txt file with information about each objects location, rotation, scale and other information
# For parsing into the game engine when loading the scene
create_scene_info_file(output_directory)
