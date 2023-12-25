// Object.cpp
#include "Object.h"

Object::Object(std::string name, Vector3 globalPosition, Vector3 rotationAxis, float rotationAngle, Vector3 scale)
    : name(std::move(name)), globalPosition(globalPosition), rotationAxis(rotationAxis), rotationAngle(rotationAngle), scale(scale), parent(nullptr) {
    
}

// Add child
void Object::addChild(std::unique_ptr<Object> child) {
    child->parent = this;
    children.push_back(std::move(child));
}

// Clear children
void Object::clearChildren() {
    // For each child, call clear children and remove them from this objects children vector
}

// Get child
Object* Object::getChild(int index) const {
    return children[index].get();
}

// Get child from name
Object* Object::getChildFromName(std::string name) const {
    for (const auto& child : children) {
        if (child->name == name) {
            return child.get();
        }

        // Recursively search for the child in this child's descendants
        Object* foundChild = child->getChildFromName(name);
        if (foundChild != nullptr) {
            return foundChild;
        }
    }

    return nullptr; // Child not found
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
        this->localPosition = Vector3Subtract(globalPosition, parent->globalPosition);
    }
    else {
        this->localPosition = globalPosition;
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
