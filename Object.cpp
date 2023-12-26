// Object.cpp
#include "Object.h"

Object::Object(std::string name, Vector3 localPosition, Vector3 rotationAxis, float rotationAngle, Vector3 scale)
    : name(std::move(name)), localPosition(localPosition), rotationAxis(rotationAxis), rotationAngle(rotationAngle), scale(scale), parent(nullptr) {
    globalPosition = localPosition;
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

// Update both position variables (ensures the local, global and parents positions are all in sync)
// ISUE WITH INHERITING LOCAL POSITION. Seems to be constantly updating local position based on global position
void Object::updatePositions() {
    if (parent != nullptr) {
        this->globalPosition = Vector3Add(parent->globalPosition, localPosition);
    }
    else {
        this->globalPosition = localPosition;
    }
}

Vector3 Object::getGlobalPosition() const {
	return globalPosition;
}

void Object::setLocalPosition(Vector3 position) {
	this->localPosition = position;
    if (parent != nullptr) {
		this->globalPosition = Vector3Add(position, parent->globalPosition);
	}
    else {
		this->globalPosition = position;
	}
}

Vector3 Object::getLocalPosition() const {
	return localPosition;
}

void Object::setRotationAxis(Vector3 rotationAxis) {
	this->rotationAxis = rotationAxis;
}

Vector3 Object::getRotationAxis() const {
	return rotationAxis;
}

void Object::setRotationAngle(float angle) {
	this->rotationAngle = angle;
}

float Object::getRotationAngle() const {
	return rotationAngle;
}

void Object::setScale(Vector3 scale) {
    this->scale = scale;
}

Vector3 Object::getScale() {
	return scale;
}

// Ready
void Object::ready() {
    // Set the local position based off the parent objects position
    if (parent != nullptr) {
		this->localPosition = Vector3Subtract(globalPosition, parent->globalPosition);
	}
    else {
		this->localPosition = globalPosition;
	}

    std::cout << "Object is ready: " << name << std::endl;

    // Ready children
    for (auto& child : children) {
        child->ready();
    }
}

// Update
void Object::update() {
    // Update this object's logic
    this->updatePositions();

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
