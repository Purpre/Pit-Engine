#pragma once
#include <memory>
#include <string>
#include <vector>

class Node
{
  protected:
	std::vector<std::unique_ptr<Node>> children;
	Node* parent = nullptr;

  public:
	std::string name;

	Node(std::string name = "Node") : name(std::move(name))
	{
	}

	virtual ~Node() = default;

	const std::vector<std::unique_ptr<Node>>& getChildren() const
	{
		return children;
	}

	template <typename T, typename... Args> T* addChild(Args&&... args)
	{
		static_assert(std::is_base_of_v<Node, T>, "T must inherit from Node");

		auto child = std::make_unique<T>(std::forward<Args>(args)...);

		T* ptr = child.get();

		child->parent = this;
		children.push_back(std::move(child));

		return ptr;
	}

	Node* getChild(const std::string& name)
	{
		for (const auto& child : children)
		{
			if (child->name == name)
				return child.get();
		}

		return nullptr;
	}
};