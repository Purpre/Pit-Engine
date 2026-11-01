#pragma once
#include <Pit/Nodes/Node.hpp>
#include <glm/vec3.hpp>

using glm::vec3;

class Node3D : public Node {
public:
    vec3 postion = vec3(0.0f, 0.0f, 0.0f);
    vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
    vec3 scale = vec3(1.0f, 1.0f, 1.0f);

    Node3D(std::string name = "Node3D")
        : Node(std::move(name)) {}
};