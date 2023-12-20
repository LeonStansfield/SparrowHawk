// MeshInstance.cpp
#include "MeshInstance.h"

MeshInstance::MeshInstance(std::string name, Vector3 position, std::string modelPath)
    : Object(std::move(name), position), modelPath(std::move(modelPath)) {}

void MeshInstance::ready() {
    Object::ready();
    loadModel();
}

void MeshInstance::draw() const {
    std::cout << "Drawing mesh instance: " << name << std::endl;
    // Draw this mesh instance
    DrawModel(model, position, 1.0f, WHITE);

    // Draw children
    Object::draw();
}

void MeshInstance::loadModel() {
    // Load the model from file
    model = LoadModel(modelPath.c_str());
}
