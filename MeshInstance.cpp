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

    if (this->name == "Suzanne.001") {
        this->setLocalPosition(Vector3Add(this->localPosition, Vector3{ 0.0f, 0.01f, 0.0f }));
    }
    if (this->name == "Cube") {
		this->setLocalPosition(Vector3Add(this->localPosition, Vector3{ 0.0f, 0.0f, 0.01f }));
	}
    if (this->name == "Cube.001") {
        this->setLocalPosition(Vector3Add(this->localPosition, Vector3{ 0.0f, 0.0f, -0.01f }));
    }
}

void MeshInstance::draw() const {
    // Draw this mesh instance using global coordinates
    DrawModelEx(model, globalPosition, rotationAxis, rotationAngle, scale, WHITE);

    // Draw children
    Object::draw();
}
