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
				exposure *= 2;
				break;
			case GLFW_KEY_KP_SUBTRACT:
				exposure > 1 ? exposure /= 2 : exposure = 1;
				break;
			case GLFW_KEY_R:
				shouldMove = !shouldMove;
				break;
			case GLFW_KEY_V:
				static int swapInterval = 0;
				glfwSwapInterval(swapInterval);
				swapInterval = swapInterval == 0 ? 1 : 0;
				break;


			// RENDER MODE
			case GLFW_KEY_0:
				currentRenderMode = TONEMAPPED;
				break;
			case GLFW_KEY_1:
				currentRenderMode = CUBE_ONLY;
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