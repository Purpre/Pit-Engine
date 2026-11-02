#pragma once
#include <Pit/Nodes/Node3D.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera3D : public Node3D
{
  public:
	int fov = 70;

	Camera3D(std::string name = "Camera3D", int fieldOfView = 70, unsigned int width = 1920, unsigned int height = 1080)
		: Node3D(std::move(name)), fov(fieldOfView), width(width), height(height)
	{
	}

	void updateCamera();
    void setShaderUniforms(unsigned int shaderProgramId);

  protected:
    unsigned int height = 1080;
    unsigned int width = 1920;

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(static_cast<float>(fov)), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);

	glm::vec3 front = {0.0f, 0.0f, -1.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};
	glm::vec3 right = {1.0f, 0.0f, 0.0f};

	void updateVectors();

	unsigned int viewLoc; // glGetUniformLocation(shader.programId, "view");
	unsigned int projLoc; // glGetUniformLocation(shader.programId, "projection");
};