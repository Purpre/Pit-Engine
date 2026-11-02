#pragma once
#include <Pit/Nodes/Node3D.hpp>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 uv;
};

class Mesh : public Node3D
{
  private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;

	void loadOBJ(const std::string& path);
	void setupMesh();

  public:
	Mesh(std::string name = "Mesh") : Node3D(std::move(name))
	{
	}

	void setModel(const std::string& path)
	{
		loadOBJ(path);
		setupMesh();
	}

	void draw();
};