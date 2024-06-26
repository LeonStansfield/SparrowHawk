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
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scale;

    Object(std::string name, Vector3 localPosition, Vector3 rotationAxis, float rotationAngle, Vector3 scale);

    void addChild(std::unique_ptr<Object> child);

    void clearChildren();

    Object* getChild(int index) const;

    Object*getChildFromName(std::string name) const;

    void printNodeTree(int depth = 0) const;

    void updatePositions();

    void setGlobalPosition(Vector3 position);

    Vector3 getGlobalPosition() const;

    void setLocalPosition(Vector3 position);

    Vector3 getLocalPosition() const;

    void setRotationAxis(Vector3 rotationAxis);

    Vector3 getRotationAxis() const;

    void setRotationAngle(float angle);

    float getRotationAngle() const;

    void setScale(Vector3 scale);

    Vector3 getScale();

    virtual void ready();

    virtual void update();

    virtual void draw() const;

private:
    std::vector<std::unique_ptr<Object>> children;
    Object* parent;
};
