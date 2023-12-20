// Object.h
#pragma once

#include <vector>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Object {
public:
    std::string name;
    Vector3 position;

    Object(std::string name, Vector3 position);

    void addChild(std::unique_ptr<Object> child);

    virtual void ready();

    virtual void update();

    virtual void draw() const;

private:
    std::vector<std::unique_ptr<Object>> children;
};
