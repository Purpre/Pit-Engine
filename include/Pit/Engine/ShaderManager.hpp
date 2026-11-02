#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const std::string vertex = R"(
#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}
)";

const std::string fragment = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

struct Shader
{
	unsigned int vertexId;
	unsigned int fragmentId;
	unsigned int programId;
};

class ShaderManager
{
  private:
	std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;

  public:
	Shader* get(const std::string& name);

	void registerShader(const std::string& name, std::string vertexPath, std::string fragmentPath, bool isPath);
};