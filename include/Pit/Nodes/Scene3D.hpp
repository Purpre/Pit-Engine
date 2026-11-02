#pragma once
#include <Pit/Nodes/Camera3D.hpp>
#include <Pit/Nodes/Node.hpp>

class Scene3D
{
  public:
	std::unique_ptr<Node> root;
	Camera3D* currentCamera = nullptr;

	void setCurrentCamera(Camera3D* camera)
	{
		currentCamera = camera;
	};

	Scene3D() : root(std::make_unique<Node>("Root"))
	{
	}
};