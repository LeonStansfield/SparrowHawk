// MeshInstance.h
#pragma once

#include "Object.h"

class MeshInstance : public Object {
public:
    std::string modelPath;
    Model model;

    MeshInstance(std::string name, Vector3 position, std::string modelPath);

    void ready() override;

    void draw() const override;

private:
    void loadModel();
};
