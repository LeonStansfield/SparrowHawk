// MeshInstance.cpp
#include "MeshInstance.h"

MeshInstance::MeshInstance(std::string name, Vector3 globalPosition, std::string modelPath)
    : Object(std::move(name), globalPosition), modelPath(std::move(modelPath)) {}

void MeshInstance::ready() {
    Object::ready();
    model = LoadModel(modelPath.c_str());
}

void MeshInstance::draw() const {
    // Draw this mesh instance using global coordinates
    DrawModel(model, globalPosition, 1.0f, WHITE);

    // Draw children
    Object::draw();
}
