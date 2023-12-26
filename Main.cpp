#include <vector>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Object.h"
#include "MeshInstance.h"
#include "SceneManager.h"


// Todo: 
// Fix rotation + scale inheritence (on import and in engine)

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
    auto root = std::make_shared<Object>("Root", Vector3{ 0.0f, 0.0f, 0.0f }, Vector3 {0.0f, 0.0f, 0.0f}, 0.0f, Vector3 {1.0f, 1.0f, 1.0f});

    // For the info in objectData, create the objects
    for (const auto& objectInfo : objectData) {
        // Extract object properties from the vector
        std::string name = objectInfo[0];
        Vector3 location = { std::stof(objectInfo[1]), std::stof(objectInfo[2]), std::stof(objectInfo[3]) };
        Vector3 axis = { std::stof(objectInfo[4]), std::stof(objectInfo[5]), std::stof(objectInfo[6]) };
        float angle = std::stof(objectInfo[7]) * (180.0f / PI);
        Vector3 scale = { std::stof(objectInfo[8]), std::stof(objectInfo[9]), std::stof(objectInfo[10]) };
        std::string meshFilepath = "Assets/Scenes/Scene_1/" + name + ".glb";

        // Create the object
        auto object = std::make_unique<MeshInstance>(name, location, axis, angle, scale, meshFilepath);

        // Add object to tree
        if (objectInfo[11] != "root") {
			// Find the parent object
            auto parent = root->getChildFromName(objectInfo[11]);
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
