#include <iostream>

#include <Pit/Engine/Application.hpp>
#include <Pit/Nodes/Node.hpp>
#include <Pit/Nodes/Node3D.hpp>
#include <Pit/Nodes/Scene3D.hpp>

using std::cout;

int main()
{
    Application::init();
    Application app("Game");

    Scene3D scene;

    auto camera = std::make_unique<Camera3D>("MainCamera");
    scene.setCurrentCamera(camera.get());

    scene.root->addChild(std::move(camera));

    auto object = std::make_unique<Node3D>("Object");
    scene.root->addChild(std::move(object));

    app.setScene(&scene);

    for (const auto& child : scene.root->getChildren())
    {
        std::cout << "Child: " << child->name << std::endl;

        for (const auto& grandchild : child->getChildren())
        {
            std::cout << "  Grandchild: " << grandchild->name << std::endl;
        }
    }

    app.run();

    return 0;
}