#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Core.h"

// Use OpenGL 3.3 Core profile for desktop, else use OpenGL 1.0
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "basic lighting");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = Vector3{ 2.0f, 4.0f, 6.0f };    // Camera position
    camera.target = Vector3{ 0.0f, 0.5f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                              // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;           // Camera projection type

    // Objects vector
    std::vector<Object*> Objects;

    MeshInstance* meshInstance = new MeshInstance(Vector3{ 0.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");
    Objects.push_back(meshInstance);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    
    // Ready
    for (int i = 0; i < Objects.size(); i++)
    {
		Objects[i]->ready(Objects);
    }

    // Main game loop
    while (!WindowShouldClose()) 
    {
        // Update
        UpdateCamera(&camera, CAMERA_ORBITAL);

        for (int i = 0; i < Objects.size(); i++){
            Objects[i]->update(Objects);
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        for (int i = 0; i < Objects.size(); i++) {
            // Check if the object is visible, and is a mesh instance or a subclass of mesh instance using a dynamic cast
            MeshInstance* meshInstance = dynamic_cast<MeshInstance*>(Objects[i]);
            if (meshInstance != nullptr && meshInstance->getVisible()) {
				// Draw the object
				((MeshInstance*)Objects[i])->draw();
            }
		}   

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    for (int i = 0; i < Objects.size(); i++) {
		Objects[i]->end();
	}

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
