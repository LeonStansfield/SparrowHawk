// MeshInstance.h
#pragma once

#include "Object.h"

class MeshInstance : public Object {
public:
    std::string modelPath;
    Model model;

    MeshInstance(std::string name, Vector3 globalPosition, std::string modelPath);

    void ready() override;

    void draw() const override;
};
