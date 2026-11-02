#include <iostream>

#include <Pit/Engine/Application.hpp>
#include <Pit/Nodes/Mesh.hpp>

using std::cout;

int main()
{
	Application::init();
	Application app("Game");

	Scene3D scene;

	auto* camera = scene.root->createChild<Camera3D>("MainCamera", 70, 800, 600);
	camera->position = {0.0f, 0.0f, 0.0f};
	camera->rotation = {0.0f, -90.0f, 0.0f};
	scene.setCurrentCamera(camera);

	auto* object = scene.root->createChild<Node3D>("Object");

	auto* mesh = object->createChild<Mesh>("Suzanne");
	mesh->rotation = {0.0f, 0.0f, 0.0f};
	mesh->setModel("Suzanne.obj");

	app.setScene(&scene);

	app.onUpdate = [mesh](float deltaTime)
	{
		mesh->position.z -= 0.5f * deltaTime;
		mesh->position.x = 2.0f * sin(glfwGetTime());
	};

	app.run(mesh);

	return 0;
}