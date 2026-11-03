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
	camera->position = {0.0f, 0.5f, 2.5f};
	camera->rotation = {0.0f, -90.0f, 0.0f};
	scene.setCurrentCamera(camera);

	auto* suzanne = scene.root->createChild<Mesh>("Suzanne");
	suzanne->position = {0.0f, 0.30f, 0.0f};
	suzanne->setModel("Suzanne.obj");
	suzanne->color = Color3::RGB(255.0f, 128.0f, 51.0f);

	auto* cube = scene.root->createChild<Mesh>("Cube");
	cube->position = {3.0f, 2.0f, -1.5f};
	cube->rotation = {0.0f, 45.0f, 0.0f};
	cube->scale = {0.5f, 0.5f, 0.5f};
	cube->setModel("Cube.obj");

	auto* cube2 = scene.root->createChild<Mesh>("Cube2");
	cube2->position = {-3.0f, 2.0f, -1.5f};
	cube2->rotation = {0.0f, 45.0f, 0.0f};
	cube2->scale = {0.5f, 0.5f, 0.5f};
	cube2->setModel("Cube.obj");

	scene.backgroundColor = Color3::RGB(100.0f, 114.0f, 162.0f);

	app.setScene(&scene);

	app.onUpdate = [suzanne, cube, cube2](float deltaTime)
	{
		cube->rotation.y -= 90.0f * deltaTime;
		cube2->rotation.y -= 90.0f * deltaTime;
		suzanne->rotation.y += 90.0f * deltaTime;
	};

	app.run();

	return 0;
}