#include <Pit/Nodes/Node.hpp>
#include <Pit/Nodes/Scene3D.hpp>
#include <Pit/Nodes/Mesh.hpp>
#include <functional>

void Node::getDescendants(const std::function<void(Node*)>& callback)
{
	callback(this);

	for (const auto& child : children)
		child->getDescendants(callback);
}

Node* Node::getChild(const std::string& name)
{
	for (const auto& child : children)
	{
		if (child->name == name)
			return child.get();
	}

	return nullptr;
}

void Node::registerMeshInScene(Mesh* mesh)
{
    if (parentScene)
        parentScene->registerMesh(mesh);
}