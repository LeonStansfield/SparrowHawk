#pragma once

#include <math.h>
#include <vector>
#include <string>

#include "raylib.h"

// Object
// Object is the base class for all objects, holds a position
class Object
{
public:
    virtual ~Object() {} // virtual destructor
    Vector3 position;

    Object();

    Object(Vector3 position);

    Vector2 getPosition();

    void setPosition(Vector3 position);

    virtual void ready(std::vector<Object*>& Objects);

    virtual void update(std::vector<Object*> Objects);

    virtual void end();
};

// Visual Intance
// Draws a colored box or texture at a position, size, and render layer
class MeshInstance : public Object
{
public:
    bool visible = true;
    std::string meshPath;
    Model model;
    Shader shader;

    MeshInstance();

    MeshInstance(Vector3 position, std::string meshPath);
    
    void setVisible(bool visibility);

    bool getVisible();

    // Overide ready() to load mesh
    void ready(std::vector<Object*>& gameObjects) override;

    void draw();

    void end() override;
};
