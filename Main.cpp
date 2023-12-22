#include <vector>
#include <iostream>
#include <memory>
#include "raylib.h"
#include "raymath.h"
#include "Object.h"
#include "MeshInstance.h"

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

    // Creating objects
    auto root = std::make_unique<Object>("Root", Vector3{ 0.0f, 0.0f, 0.0f });
    auto obj1 = std::make_unique<MeshInstance>("Object 1", Vector3{ 3.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");
    auto obj2 = std::make_unique<MeshInstance>("Object 2", Vector3{ -6.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");

    // Building the tree
    root->addChild(std::move(obj1));
    root->getChild(0)->addChild(std::move(obj2));

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
