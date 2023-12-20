// Object.cpp
#include "Object.h"

Object::Object(std::string name, Vector3 globalPosition)
    : name(std::move(name)), globalPosition(globalPosition), parent(nullptr) {
    localPosition = globalPosition;
}

void Object::addChild(std::unique_ptr<Object> child) {
    child->parent = this;
    children.push_back(std::move(child));
}

Object* Object::getChild(int index) const {
    return children[index].get();
}

void Object::printNodeTree(int depth) const {
	// Print this object's name
	std::cout << std::string(depth, '-') << name << std::endl;

	// Print children
    for (const auto& child : children) {
		child->printNodeTree(depth + 1);
	}
}

void Object::ready() {
    std::cout << "Object is ready: " << name << std::endl;

    // Calculate local position based on parent's global position and its global position
    if (parent) {
        localPosition = Vector3Subtract(globalPosition, parent->globalPosition);
    }

    // Ready children
    for (auto& child : children) {
        child->ready();
    }
}

void Object::update() {
    // Update this object's logic
    
    // Update global position based on parent's global position and local position
    if (parent) {
        globalPosition = Vector3Add(parent->globalPosition, localPosition);
    }

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
