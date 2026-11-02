#include <iostream>

#include <Pit/Engine/Application.hpp>
#include <Pit/Nodes/Mesh.hpp>

using std::cout;

int main()
{
	const unsigned int width = 1920;
	const unsigned int height = 1080;

	Application::init();
	Application app("Game", width, height);

	Scene3D scene;

	auto* camera = scene.root->createChild<Camera3D>("MainCamera", 70, width, height);
	camera->position = {0.0f, 1.0f, 2.5f};
	camera->rotation = {-20.0f, -90.0f, 0.0f};
	scene.setCurrentCamera(camera);

	auto* object = scene.root->createChild<Node3D>("Object");

	auto* mesh = object->createChild<Mesh>("Suzanne");
	mesh->rotation = {0.0f, -15.0f, 0.0f};
	mesh->setModel("Suzanne.obj");

	app.setScene(&scene);

	app.onUpdate = [mesh](float deltaTime)
	{
	};

	app.run(mesh);

	return 0;
}