#pragma once
#include <Pit/Nodes/Camera3D.hpp>
#include <Pit/Nodes/Node.hpp>
#include <Pit/Nodes/Mesh.hpp>
#include <Pit/Engine/Color3.hpp>
#include <vector>

class Scene3D
{
  public:
	Color3::RGB backgroundColor = {25.0f, 25.0f, 38.25f};

	std::vector<Mesh*> meshes;
	void registerMesh(Mesh* mesh)
	{
		meshes.push_back(mesh);
	}
	
	std::unique_ptr<Node> root;
	Camera3D* currentCamera = nullptr;

	void setCurrentCamera(Camera3D* camera)
	{
		currentCamera = camera;
	};

	Scene3D() : root(std::make_unique<Node>("Root", this))
	{
	}
};