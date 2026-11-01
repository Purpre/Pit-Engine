#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Application
{
public:

    static void init();

    std::string name;
    GLFWwindow *win;
    bool running = false;

    void run();

    void update();
    void render();

    Application(
        std::string window_name,
        int width = 800,
        int height = 600
    );

};