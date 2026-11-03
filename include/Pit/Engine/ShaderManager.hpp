#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const std::string vertex = R"(
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 aObjectColor;

out vec3 Normal;
out vec3 FragPos;
out vec3 ObjectColor;

void main()
{
    vec4 worldPosition = model * vec4(aPosition, 1.0);

    FragPos = worldPosition.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalize(normalMatrix * aNormal);

    ObjectColor = aObjectColor;

    gl_Position = projection * view * worldPosition;
}
)";

const std::string fragment = R"(
#version 330 core

in vec3 Normal;
in vec3 ObjectColor;

out vec4 FragColor;

void main()
{
    vec3 ambientColor = vec3(1.0, 1.0, 1.0);
    vec3 lightDirection = normalize(vec3(-0.5, -1.0, -0.5));

    float ambient = 0.15;
    float diffuse = max(dot(normalize(Normal), normalize(-lightDirection)), 0.0);

    vec3 lighting = ambientColor * (ambient + diffuse);

    FragColor = vec4(ObjectColor * lighting, 1.0);
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