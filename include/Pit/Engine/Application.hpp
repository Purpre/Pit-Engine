#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Pit/Nodes/Mesh.hpp>
#include <Pit/Nodes/Scene3D.hpp>

class Application
{
public:

    static void init();

    std::string name;
    GLFWwindow *win = nullptr;
    bool running = false;
    
    Scene3D* currentScene = nullptr;

    void setScene(Scene3D* scene)
    {
        currentScene = scene;
    }

    float lastFrame = 0.0f;

    void run(Mesh* mesh);

    void update(float deltaTime);
    void render();

    Application(
        std::string window_name,
        int width = 800,
        int height = 600
    );

};