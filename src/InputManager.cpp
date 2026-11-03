#include <Pit/Engine/InputManager.hpp>
#include <iostream>

bool Input::currentKeys[GLFW_KEY_LAST + 1] = {};
bool Input::previousKeys[GLFW_KEY_LAST + 1] = {};

double Input::mouseXPos = 0.0f;
double Input::mouseYPos = 0.0f;

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return;

	if (action == GLFW_PRESS)
		currentKeys[key] = true;
	else if (action == GLFW_RELEASE)
		currentKeys[key] = false;
}

void Input::update()
{
	for (int key = 0; key <= GLFW_KEY_LAST; key++)
		previousKeys[key] = currentKeys[key];
}

bool Input::isKeyDown(int key)
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return false;

	return currentKeys[key];
}

bool Input::isKeyPressed(int key)
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return false;

	return currentKeys[key] && !previousKeys[key];
}

bool Input::isKeyReleased(int key)
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return false;

	return !currentKeys[key] && previousKeys[key];
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	mouseXPos = xpos;
	mouseYPos = ypos;
}