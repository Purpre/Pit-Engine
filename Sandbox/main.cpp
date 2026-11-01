#include <iostream>

#include <Pit/Application.hpp>

int main()
{
    Application::init();

    Application app("Game");

    std::cout << app.name << "\n";

    app.run();

    return 0;
}