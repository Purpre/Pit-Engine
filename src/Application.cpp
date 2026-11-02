#include <Pit/Engine/Application.hpp>
#include <Pit/Nodes/Camera3D.hpp>
#include <memory>

using std::cout, std::cerr;

void Application::init()
{
	glfwSetErrorCallback([](int error, const char* description)
						 { std::cerr << "GLFW Error " << error << ": " << description << '\n'; });

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Application::Application(std::string window_name, int width, int height)
{
	this->name = window_name;

	if (!glfwInit())
	{
		cerr << "Failed to initialize GLFW\n";
		throw std::runtime_error("Failed to initialize GLFW");
	}

	this->win = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);

	if (!win)
	{
		glfwTerminate();
		cerr << "Failed to create window\n";
		throw std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(this->win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(win);
		win = nullptr;
		glfwTerminate();
		cerr << "Failed to initialize GLAD\n";
		throw std::runtime_error("Failed to initialize GLAD");
	}

	shaderManager.registerShader("default", vertex, fragment, false);

	cout << "Window created: " << window_name << " (" << width << "x" << height << ")\n";
	this->running = true;
}

void Application::run(Mesh* mesh)
{
	if (!win || !running)
		return;

	while (running && !glfwWindowShouldClose(win))
	{
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		update(deltaTime);
		render();

		glfwSwapBuffers(win);
	}
}

void Application::update(float deltaTime)
{
	// Engine update logic

	if (onUpdate)
		onUpdate(deltaTime);
}

void Application::render()
{
	if (onRenderStart)
		onRenderStart();

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderManager.get("default")->programId);
	currentScene->currentCamera->setShaderUniforms(shaderManager.get("default")->programId);
	currentScene->currentCamera->updateCamera();

	unsigned int modelLoc = glGetUniformLocation(shaderManager.get("default")->programId, "model");

	for (const auto& mesh : currentScene->meshes)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, mesh->position);
		model = glm::rotate(model, glm::radians(mesh->rotation.x), {1.0f, 0.0f, 0.0f});
		model = glm::rotate(model, glm::radians(mesh->rotation.y), {0.0f, 1.0f, 0.0f});
		model = glm::rotate(model, glm::radians(mesh->rotation.z), {0.0f, 0.0f, 1.0f});
		model = glm::scale(model, mesh->scale);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		mesh->draw();
	}

	if (onRenderEnd)
		onRenderEnd();
}