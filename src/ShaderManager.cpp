#include "Pit/Engine/ShaderManager.hpp"
#include <fstream>
#include <sstream>
#include <string>

std::string ReadFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		throw std::runtime_error("Failed to open shader file: " + path);

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}

void ShaderManager::registerShader(const std::string& name, std::string vertex, std::string fragment, bool isPath)
{
	auto shader = std::make_unique<Shader>();

	std::string vertSRC;
	std::string fragSRC;

	if (isPath)
	{
		vertSRC = ReadFile(vertex);
		fragSRC = ReadFile(fragment);
	}
	else
	{
		vertSRC = vertex;
		fragSRC = fragment;
	}

	const char* CvertSRC = vertSRC.c_str();
	const char* CfragSRC = fragSRC.c_str();

	shader->vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->vertexId, 1, &CvertSRC, NULL);
	glCompileShader(shader->vertexId);

	shader->fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->fragmentId, 1, &CfragSRC, NULL);
	glCompileShader(shader->fragmentId);

	shader->programId = glCreateProgram();
	glAttachShader(shader->programId, shader->vertexId);
	glAttachShader(shader->programId, shader->fragmentId);
	glLinkProgram(shader->programId);

	glDeleteShader(shader->vertexId);
	glDeleteShader(shader->fragmentId);

	shaders[name] = std::move(shader);
}

Shader* ShaderManager::get(const std::string& name)
{
	auto it = shaders.find(name);

	if (it == shaders.end())
		return nullptr;

	return it->second.get();
}