// Object.cpp
#include "Object.h"

Object::Object(std::string name, Vector3 localPosition)
    : name(std::move(name)), localPosition(localPosition), parent(nullptr) {
    this->globalPosition = localPosition;
}

// Add child
void Object::addChild(std::unique_ptr<Object> child) {
    child->parent = this;
    children.push_back(std::move(child));
}

// Get child
Object* Object::getChild(int index) const {
    return children[index].get();
}

// Print node tree
void Object::printNodeTree(int depth) const {
	// Print this object's name
	std::cout << std::string(depth, '-') << name << std::endl;

	// Print children
    for (const auto& child : children) {
		child->printNodeTree(depth + 1);
	}
}

// Update global position
void Object::updateGlobalPosition() {
    if (parent != nullptr) {
        this->globalPosition = Vector3Add(parent->globalPosition, localPosition);
    }
    else {
        this->globalPosition = localPosition;
    }
}

void Object::setGlobalPosition(Vector3 position) {
    this->globalPosition = position;
    if (parent != nullptr) {
		this->localPosition = Vector3Subtract(position, parent->globalPosition);
	}
    else {
		this->localPosition = position;
	}

}

// Ready
void Object::ready() {
    this->updateGlobalPosition();

    std::cout << "Object is ready: " << name << std::endl;

    // Ready children
    for (auto& child : children) {
        child->ready();
    }
}

// Update
void Object::update() {
    // Update this object's logic
    this->updateGlobalPosition();

    // Update children
    for (auto& child : children) {
        child->update();
    }
}

// Draw
void Object::draw() const {
    // Draw this object

    // Draw children
    for (const auto& child : children) {
        child->draw();
    }
}
