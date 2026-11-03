#pragma once

#include <GLFW/glfw3.h>

class Input
{
  private:
	static bool currentKeys[GLFW_KEY_LAST + 1];
	static bool previousKeys[GLFW_KEY_LAST + 1];

  public:
	static double mouseXPos;
	static double mouseYPos;
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void update();

	static bool isKeyDown(int key);
	static bool isKeyPressed(int key);
	static bool isKeyReleased(int key);
};