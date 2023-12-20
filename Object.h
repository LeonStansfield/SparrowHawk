// Object.h
#pragma once

#include <vector>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

class Object {
public:
    std::string name;
    Vector3 localPosition;  // Local coordinates relative to the parent
    Vector3 globalPosition; // Global coordinates relative to the global origin

     Object(std::string name, Vector3 globalPosition);

    void addChild(std::unique_ptr<Object> child);

    // Get child function
    Object* getChild(int index) const;

    void printNodeTree(int depth = 0) const;

    virtual void ready();

    virtual void update();

    virtual void draw() const;

private:
    std::vector<std::unique_ptr<Object>> children;
    Object* parent;
};
