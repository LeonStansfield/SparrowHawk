#include "SceneManager.h"

SceneManager::SceneManager() {
}

std::vector<std::vector<std::string>> SceneManager::loadScene(std::string sceneName) {
    // Open the scene file
    std::ifstream sceneFile(sceneName);
    if (!sceneFile.is_open()) {
        std::cerr << "Failed to open scene file: " << sceneName << std::endl;
        return {};
    }

    std::cout << "Loading scene: " << sceneName << std::endl;

    std::string name = "";
    Vector3 location = { 0.0f, 0.0f, 0.0f };
    Vector3 rotation_axis = { 0.0f, 0.0f, 0.0f };
    float rotation_angle = 0.0f;
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    std::string parent = "";

    std::vector<std::vector<std::string>> objectData;
    std::string line;
    while (std::getline(sceneFile, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        // If line starts with 'Object'
        if (line.find("Object") == 0) {
            // Set the name to the second word in the line
            name = line.substr(line.find(" ") + 1);
            // Remove space from start of name
            name.erase(0, name.find_first_not_of(" "));
        }
        // If line starts with 'Location'
        else if (line.find("Location") == 0) {
            // Set the location to the values between the brackets
            float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
            float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
            float z = std::stof(line.substr(line.find_last_of(" ") + 1));
            location = Vector3{ x, y, z };
        }
        // If line starts with 'Rotation'
        else if (line.find("RotationAxis") == 0) {
            // Set the rotation axis to the values between the brackets
            float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
            float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
            float z = std::stof(line.substr(line.find_last_of(" ") + 1));
            rotation_axis = Vector3{ x, y, z };
        }
        else if (line.find("RotationAngle") == 0) {
            // Set the rotation angle to the rotation angle float
            rotation_angle = std::stof(line.substr(line.find_last_of(" ") + 1));
        }
        // If line starts with 'Scale'
        else if (line.find("Scale") == 0) {
            // Set the scale to the values between the brackets
            float x = std::stof(line.substr(line.find("(") + 1, line.find(",") - line.find("(") - 1));
            float y = std::stof(line.substr(line.find(",") + 1, line.find(")") - line.find(",") - 1));
            float z = std::stof(line.substr(line.find_last_of(" ") + 1));
            scale = Vector3{ x, y, z };
        }
        // If line starts with 'Parent'
        else if (line.find("Parent") == 0) {
            // Set the parent to the second word in the line
            parent = line.substr(line.find(" ") + 1);
            // Remove space from start of parent
            parent.erase(0, parent.find_first_not_of(" "));
        }
        // If line starts with 'ObjectEnd'
        else if (line.find("End") == 0) {
            // All object data is parsed, create object
            std::cout << name << std::endl;
            std::cout << location.x << ", " << location.y << ", " << location.z << std::endl;
            std::cout << rotation_axis.x << ", " << rotation_axis.y << ", " << rotation_axis.z << std::endl;
            std::cout << rotation_angle << std::endl;
            std::cout << scale.x << ", " << scale.y << ", " << scale.z << std::endl;
            std::cout << parent << std::endl;

            // Add object data to the vector
            objectData.push_back({ name, 
                std::to_string(location.x), std::to_string(location.y), std::to_string(location.z),
                std::to_string(rotation_axis.x), std::to_string(rotation_axis.y), std::to_string(rotation_axis.z), 
                std::to_string(rotation_angle),
                std::to_string(scale.x), std::to_string(scale.y), std::to_string(scale.z), parent });
        }
    }

    sceneFile.close();

    return objectData;
}