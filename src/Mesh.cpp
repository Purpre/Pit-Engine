#include <Pit/Nodes/Mesh.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

void Mesh::loadOBJ(const std::string& path)
{
	tinyobj::ObjReaderConfig config;
	config.triangulate = true;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(path))
	{
		throw std::runtime_error("Failed to load OBJ: " + path + "\n" + reader.Error());
	}

	if (!reader.Warning().empty())
	{
		std::cerr << "OBJ warning: " << reader.Warning() << '\n';
	}

	const auto& attrib = reader.GetAttrib();
	const auto& shapes = reader.GetShapes();

	vertices.clear();
	indices.clear();

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			Vertex vertex{};

			// Position
			vertex.position = {attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1],
							   attrib.vertices[3 * index.vertex_index + 2]};

			// Normal
			if (index.normal_index >= 0)
			{
				vertex.normal = {attrib.normals[3 * index.normal_index + 0], attrib.normals[3 * index.normal_index + 1],
								 attrib.normals[3 * index.normal_index + 2]};
			}

			// UV
			if (index.texcoord_index >= 0)
			{
				vertex.uv = {attrib.texcoords[2 * index.texcoord_index + 0],
							 attrib.texcoords[2 * index.texcoord_index + 1]};
			}

			vertices.push_back(vertex);
			indices.push_back(static_cast<unsigned int>(indices.size()));
		}
	}
}

void Mesh::setupMesh()
{
	// Generate and bind the VAO, VBO, and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Activates VAO
	glBindVertexArray(VAO);

	// Sends the vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// Sends the indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}