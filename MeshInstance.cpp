// MeshInstance.cpp
#include "MeshInstance.h"

MeshInstance::MeshInstance(std::string name, Vector3 localPosition, std::string modelPath)
    : Object(std::move(name), localPosition), modelPath(std::move(modelPath)) {}

void MeshInstance::ready() {
    Object::ready();
    model = LoadModel(modelPath.c_str());
}

void MeshInstance::update() {
	Object::update();
    if (this->name == "Object 1") {
        this->localPosition.x += 0.01f;
    }
    else if (this->name == "Object 2") {
        setGlobalPosition(Vector3 {0.0f, -3.0f, 0.0f});
    }
}

void MeshInstance::draw() const {
    // Draw this mesh instance using global coordinates
    DrawModel(model, globalPosition, 1.0f, WHITE);

    // Draw children
    Object::draw();
}
