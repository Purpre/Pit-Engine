#pragma once
#include <Pit/Nodes/Node3D.hpp>

class Camera3D : public Node3D {
public:
    int fov = 70;

    Camera3D(std::string name = "Camera3D")
        : Node3D(std::move(name)) {}
};