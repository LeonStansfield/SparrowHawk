// MeshInstance.cpp
#include "MeshInstance.h"

MeshInstance::MeshInstance(std::string name, Vector3 localPosition, Vector3 rotationAxis, float rotationAngle, Vector3 scale, std::string modelPath)
    : Object(std::move(name), localPosition, rotationAxis, rotationAngle, scale), modelPath(std::move(modelPath)) {}

void MeshInstance::ready() {
    Object::ready();
    model = LoadModel(modelPath.c_str());
}

void MeshInstance::update() {
	Object::update();
}

void MeshInstance::draw() const {
    // Draw this mesh instance using global coordinates
    DrawModelEx(model, globalPosition, rotationAxis, rotationAngle, scale, WHITE);

    // Draw children
    Object::draw();
}
