#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "raylib.h"
#include "raymath.h"
#include "Core.h"

// Object
Object::Object()
{
	position = { 0, 0, 0 };
}

Object::Object(Vector3 position)
{
	this->position = { position.x, position.y, position.z };
}

Vector2 Object::getPosition()
{
	return { position.x, position.y };
}

void Object::setPosition(Vector3 position)
{
	this->position = { position.x, position.y, position.z };
}

void Object::ready(vector<Object*>& Objects)
{
	// Do nothing
}

void Object::update(vector<Object*> Objects)
{
	// Do nothing
}

void Object::end()
{
	delete this;
}

// Mesh Instance
MeshInstance::MeshInstance()
{
	position = { 0, 0, 0 };
	meshPath = "";
	visible = true;
}

MeshInstance::MeshInstance(Vector3 position, string meshPath)
{
	this->position = { position.x, position.y, position.z };
	this->meshPath = meshPath;
	visible = true;
}

void MeshInstance::setVisible(bool visibility)
{
	visible = visibility;
}

bool MeshInstance::getVisible()
{
	return visible;
}

void MeshInstance::ready(vector<Object*>& Objects)
{
	// Load mesh
	model = LoadModel(meshPath.c_str());
	// Set shaders
	model.materials[0].shader = shader;
}

void MeshInstance::draw()
{
	if (visible)
	{
		// Draw mesh
		DrawModel(model, { position.x, position.y, position.z }, 1.0f, WHITE);
	}
}

void MeshInstance::end()
{
	// Unload mesh
	UnloadModel(model);
	delete this;
}
