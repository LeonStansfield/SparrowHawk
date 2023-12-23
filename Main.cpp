#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "raylib.h"
#include "raymath.h"
#include "Object.h"
#include "MeshInstance.h"


// ISSUES TO FIX
// 1. Upgrade mesh rendering to make use of rotation an scale
// 2. Exporting from blender should automatically bake the materials to textures
// 3. Should be able to create multiple different types of objects
class SceneManager {
public:
    SceneManager() {
    }

    std::vector<std::vector<std::string>> loadScene(std::string sceneName) {
        // Open the scene file
        std::ifstream sceneFile(sceneName);
        if (!sceneFile.is_open()) {
            std::cerr << "Failed to open scene file: " << sceneName << std::endl;
            return {};
        }

        std::cout << "Loading scene: " << sceneName << std::endl;

        std::string name = "";
        Vector3 location = { 0.0f, 0.0f, 0.0f };
        Vector3 rotation = { 0.0f, 0.0f, 0.0f };
        Vector3 scale = { 1.0f, 1.0f, 1.0f };
        std::string parent = "";

        std::vector<std::vector<std::string>> objectData;
        std::string line;
        while (std::getline(sceneFile, line)) {
            // Skip empty lines
            if (line.empty()) {
				continue;
			}
            // If line starts with 'Object'
            if (line.find("Object") == 0) {
                // Set the name to the second word in the line
                name = line.substr(line.find(" ") + 1);
                // Remove space from start of name
                name.erase(0, name.find_first_not_of(" "));
			}
            // If line starts with 'Location'
            else if (line.find("Location") == 0) {
				// Set the location to the values between the brackets
                float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
                float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
                float z = std::stof(line.substr(line.find_last_of(" ") + 1));
                location = Vector3{ x, y, z };
            }
            // If line starts with 'Rotation'
            else if (line.find("Rotation") == 0) {
                // Set the rotation to the values between the brackets
                float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
                float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
                float z = std::stof(line.substr(line.find_last_of(" ") + 1));
                rotation = Vector3{ x, y, z };
            }
            // If line starts with 'Scale'
            else if (line.find("Scale") == 0) {
                // Set the scale to the values between the brackets
                float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
                float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
                float z = std::stof(line.substr(line.find_last_of(" ") + 1));
                scale = Vector3{ x, y, z };
            }
            // If line starts with 'Parent'
            else if (line.find("Parent") == 0) {
                // Set the parent to the second word in the line
                parent = line.substr(line.find(" ") + 1);
                // Remove space from start of parent
                parent.erase(0, parent.find_first_not_of(" "));
            }
            // If line starts with 'ObjectEnd'
            else if (line.find("End") == 0) {
                // All object data is parsed, create object
                std::cout << name << std::endl;
                std::cout << location.x << ", " << location.y << ", " << location.z << std::endl;
                std::cout << rotation.x << ", " << rotation.y << ", " << rotation.z << std::endl;
                std::cout << scale.x << ", " << scale.y << ", " << scale.z << std::endl;
                std::cout << parent << std::endl;

                // Add object data to the vector
                objectData.push_back({ name, std::to_string(location.x), std::to_string(location.y), std::to_string(location.z),
                    std::to_string(rotation.x), std::to_string(rotation.y), std::to_string(rotation.z),
                    std::to_string(scale.x), std::to_string(scale.y), std::to_string(scale.z), parent });
            }
        }

        sceneFile.close();

        return objectData;
    }
};

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "basic lighting");

    Camera camera = { 0 };
    camera.position = Vector3{ 2.0f, 4.0f, 6.0f };
    camera.target = Vector3{ 0.0f, 0.5f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    // Load the scene data
    SceneManager sceneManager;
    std::vector<std::vector<std::string>> objectData = sceneManager.loadScene("Assets/Scenes/Scene_1/scene.txt");

    // Create the root object
    auto root = std::make_shared<Object>("Root", Vector3{ 0.0f, 0.0f, 0.0f });

    // For the info in objectData, create the objects
    for (const auto& objectInfo : objectData) {
        // Extract object properties from the vector
        std::string name = objectInfo[0];
        Vector3 location = { std::stof(objectInfo[1]), std::stof(objectInfo[2]), std::stof(objectInfo[3]) };
        Vector3 rotation = { std::stof(objectInfo[4]), std::stof(objectInfo[5]), std::stof(objectInfo[6]) };
        Vector3 scale = { std::stof(objectInfo[7]), std::stof(objectInfo[8]), std::stof(objectInfo[9]) };
        std::string meshFilepath = "Assets/Scenes/Scene_1/" + name + ".glb";

        // Create the object
        auto object = std::make_unique<MeshInstance>(name, location, meshFilepath);

        // Add object to tree
        if (objectInfo[10] != "") {
			// Find the parent object
            auto parent = root->getChildFromName(objectInfo[10]);
            if (parent != nullptr) {
				parent->addChild(std::move(object));
			}
            else {
				std::cout << "Parent not found" << std::endl;
			}
		}
        else {
            root->addChild(std::move(object));
        }        
    }

    // Ready
    root->ready();
    root->printNodeTree();

    while (!WindowShouldClose()) {
        // Update
        root->update();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawGrid(10, 1.0f);

        // Draw the mesh instance and its children
        root->draw();

        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
