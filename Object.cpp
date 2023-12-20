// Object.cpp
#include "Object.h"

Object::Object(std::string name, Vector3 position) : name(std::move(name)), position(position) {}

void Object::addChild(std::unique_ptr<Object> child) {
    children.push_back(std::move(child));
}

void Object::ready() {
    std::cout << "Object is ready: " << name << std::endl;

    // Ready children
    for (auto& child : children) {
        child->ready();
    }
}

void Object::update() {
    std::cout << "Updating object: " << name << std::endl;

    // Update this object's logic

    // Update children
    for (auto& child : children) {
        child->update();
    }
}

void Object::draw() const {
    // Draw this object

    // Draw children
    for (const auto& child : children) {
        child->draw();
    }
}
