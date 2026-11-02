#include <iostream>

#include <Pit/Engine/Application.hpp>
#include <Pit/Nodes/Mesh.hpp>

using std::cout;

int main()
{
	Application::init();
	Application app("Game");

	Scene3D scene;

	auto* camera = scene.root->addChild<Camera3D>("MainCamera");
	scene.setCurrentCamera(camera);

	auto* object = scene.root->addChild<Node3D>("Object");

	auto* mesh = object->addChild<Mesh>("Mesh");
	mesh->setModel("Suzanne.obj");

	app.setScene(&scene);


	for (const auto& child : scene.root->getChildren())
	{
		std::cout << "Child: " << child->name << std::endl;

		for (const auto& grandchild : child->getChildren())
		{
			std::cout << "  Grandchild: " << grandchild->name << std::endl;
		}
	}

	app.run(mesh);

	return 0;
}