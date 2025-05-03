#include <algorithm>

#include "../headers/globals.h"

void reshape(GLFWwindow* window, int w, int h)
{
	w = w < 1 ? 1 : w;
	h = h < 1 ? 1 : h;

	gWidth = w;
	gHeight = h;

	glViewport(0, 0, w, h);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		savePressedKey(key, scancode);
		switch (key) {
			case GLFW_KEY_Q:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_KP_ADD:
				exposure++;
				break;
			case GLFW_KEY_KP_SUBTRACT:
				exposure--;
				break;
			default: ;
		}
	}
}

void setCallbacks() {
    glfwSetKeyCallback(window, keyboard);
    glfwSetWindowSizeCallback(window, reshape);
    reshape(window, gWidth, gHeight);
}