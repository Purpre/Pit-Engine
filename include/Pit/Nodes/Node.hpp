#pragma once
#include <memory>
#include <string>
#include <functional>
#include <vector>

class Mesh;

class Scene3D;

class Node
{
  protected:
	std::vector<std::unique_ptr<Node>> children;
	Node* parent = nullptr;
	Scene3D* parentScene = nullptr;

	void registerMeshInScene(Mesh* mesh);

  public:
	std::string name;

	Node(std::string name = "Node", Scene3D* scene = nullptr) : name(std::move(name)), parentScene(scene)
	{
	}

	virtual ~Node() = default;

	const std::vector<std::unique_ptr<Node>>& getChildren() const
	{
		return children;
	}

	template <typename T, typename... Args> T* createChild(Args&&... args)
	{
		static_assert(std::is_base_of_v<Node, T>, "T must inherit from Node");

		auto child = std::make_unique<T>(std::forward<Args>(args)...);

		T* ptr = child.get();

		child->parent = this;
		child->parentScene = this->parentScene;
		if (auto mesh = dynamic_cast<Mesh*>(child.get()))
		{
			registerMeshInScene(mesh);
		}
		children.push_back(std::move(child));

		return ptr;
	}

	Node* getChild(const std::string& name);

	void getDescendants(const std::function<void(Node*)>& callback);
};