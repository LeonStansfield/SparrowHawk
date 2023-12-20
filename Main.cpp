#include <vector>
#include <iostream>
#include <memory>
#include "raylib.h"
#include "raymath.h"

class Object {
public:
    std::string name;
    Vector3 position;

    Object(std::string name, Vector3 position) : name(std::move(name)), position(position) {}

    void addChild(std::unique_ptr<Object> child) {
        children.push_back(std::move(child));
    }

    virtual void ready() {
        std::cout << "Object is ready: " << name << std::endl;

        // Ready children
        for (auto& child : children) {
            child->ready();
        }
    }

    virtual void update() {
        std::cout << "Updating object: " << name << std::endl;

        // Update this object's logic

        // Update children
        for (auto& child : children) {
            child->update();
        }
    }

    virtual void draw() const {
        // Draw this object

        // Draw children
        for (const auto& child : children) {
            child->draw();
        }
    }

private:
    std::vector<std::unique_ptr<Object>> children;
};

class MeshInstance : public Object {
public:
    std::string modelPath;
    Model model;

    MeshInstance(std::string name, Vector3 position, std::string modelPath)
        : Object(std::move(name), position), modelPath(std::move(modelPath)) {}

    void ready() override {
        Object::ready();
        loadModel();
    }

    void draw() const override {
        std::cout << "Drawing mesh instance: " << name << std::endl;
        // Draw this mesh instance
        DrawModel(model, position, 1.0f, WHITE);

        // Draw children
        Object::draw();
    }

private:
    void loadModel() {
        // Load the model from file
        model = LoadModel(modelPath.c_str());
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

    // Creating objects
    auto obj1 = std::make_unique<MeshInstance>("Object 1", Vector3{ 0.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");
    auto obj2 = std::make_unique<MeshInstance>("Object 2", Vector3{ 3.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");
    auto obj3 = std::make_unique<MeshInstance>("Object 3", Vector3{ -3.0f, 0.0f, 0.0f }, "Assets/Suzanne.glb");

    // Building the tree
    obj1->addChild(std::move(obj2));
    obj1->addChild(std::move(obj3));

    auto obj4 = std::make_unique<Object>("Object 4", Vector3{ 0.0f, 3.0f, 0.0f });
    auto obj5 = std::make_unique<Object>("Object 5", Vector3{ 0.0f, -3.0f, 0.0f });

    obj1->addChild(std::move(obj4));
    obj1->addChild(std::move(obj5));

    // Ready
    obj1->ready();

    while (!WindowShouldClose()) {
        // Update
        obj1->update();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawGrid(10, 1.0f);

        // Draw the mesh instance and its children
        obj1->draw();

        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}
