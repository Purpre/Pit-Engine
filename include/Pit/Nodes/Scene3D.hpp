#pragma once
#include <Pit/Nodes/Node.hpp>
#include <Pit/Nodes/Camera3D.hpp>

class Scene3D
{
public:
    std::unique_ptr<Node> root;
    Camera3D* currentCamera = nullptr;

    void setCurrentCamera(Camera3D* camera)
    {
        currentCamera = camera;
    };

    Scene3D()
        : root(std::make_unique<Node>("Root")) {}
};