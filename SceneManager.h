// Scene Manager
#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include "raylib.h"
#include "raymath.h"

// ISSUES TO FIX
// 1. Upgrade mesh rendering to make use of rotation an scale
// 2. Exporting from blender should automatically bake the materials to textures
// 3. Should be able to create multiple different types of objects

class SceneManager {
public:
    SceneManager();

    std::vector<std::vector<std::string>> loadScene(std::string sceneName);
};
