// MeshInstance.h
#pragma once

#include "Object.h"

class MeshInstance : public Object {
public:
    std::string modelPath;
    Model model;

    MeshInstance(std::string name, Vector3 localPosition, Vector3 rotationAxis, float rotationAngle, Vector3 scale, std::string modelPath);

    void ready() override;

    void update() override;

    void draw() const override;
};
