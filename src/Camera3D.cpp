#include <Pit/Nodes/Camera3D.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Camera3D::updateVectors()
{
	float yaw = glm::radians(rotation.y);
	float pitch = glm::radians(rotation.x);

	glm::vec3 direction;

	direction.x = cos(yaw) * cos(pitch);
	direction.y = sin(pitch);
	direction.z = sin(yaw) * cos(pitch);

	front = glm::normalize(direction);

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

	up = glm::normalize(glm::cross(right, front));
}

void Camera3D::updateCamera()
{
	updateVectors();

	view = glm::lookAt(position, position + front, up);
	projection = glm::perspective(glm::radians(static_cast<float>(fov)),
								  static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera3D::setShaderUniforms(unsigned int shaderProgramId)
{
	viewLoc = glGetUniformLocation(shaderProgramId, "view");
	projLoc = glGetUniformLocation(shaderProgramId, "projection");
}