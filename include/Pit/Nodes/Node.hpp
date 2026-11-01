#pragma once
#include <memory>
#include <string>
#include <vector>

class Node {
protected:
    std::vector<std::unique_ptr<Node>> children;
    Node* parent = nullptr;

public:
    std::string name;

    Node(std::string name = "Node")
        : name(std::move(name)) {}
    virtual ~Node() = default;

    void addChild(std::unique_ptr<Node> child)
    {
        if (!child)
            return;

        child->parent = this;
        children.push_back(std::move(child));
    }

    const std::vector<std::unique_ptr<Node>>& getChildren() const
    {
        return children;
    }
};