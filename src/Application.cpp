#include <Pit/Application.hpp>

using std::cout, std::cerr;

void Application::init()
{
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error " << error << ": " << description << '\n';
    });

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Application::Application(
        std::string window_name,
        int width,
        int height
    )
{
    this->name = window_name;

    this->win = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
    if (this->win == NULL)
    {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to init GLAD\n";
        glfwTerminate();
        return;
    }

    cout << "Window created: " << window_name << " (" << width << "x" << height << ")\n";
    this->running = true;
}

void Application::run()
{
    while (running && !glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        update();
        render();

        glfwSwapBuffers(win);
    }
}

void Application::update()
{
    // Atualização da engine
}

void Application::render()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}