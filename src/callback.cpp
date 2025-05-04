#include <algorithm>

#include "../headers/globals.h"

void reshape(GLFWwindow* window, int w, int h)
{
	w = w < 1 ? 1 : w;
	h = h < 1 ? 1 : h;

	gWidth = w;
	gHeight = h;

	glViewport(0, 0, w, h);
	initGBuffer();
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		savePressedKey(key, scancode);
		switch (key) {
			case GLFW_KEY_Q:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;

			case GLFW_KEY_R:
				shouldMove = !shouldMove;
			break;
			case GLFW_KEY_V:
				static int swapInterval = 1;
			swapInterval = swapInterval == 0 ? 1 : 0;
			glfwSwapInterval(swapInterval);
			break;
			case GLFW_KEY_SPACE:
				lastPressedKey = "SPACE";
			static bool isFullScreen = true;
			if (!isFullScreen) {
				// Save current window position and size
				glfwGetWindowPos(window, &windowedXPos, &windowedYPos);
				glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

				// Get primary monitor and video mode
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				// Set full screen
				glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
				isFullScreen = true;
			} else {
				// Return to windowed mode
				glfwSetWindowMonitor(window, NULL, windowedXPos, windowedYPos, windowedWidth, windowedHeight, 0);
				isFullScreen = false;
			}

			// Exposure control
			case GLFW_KEY_KP_ADD:
				exposure *= 2;
				break;
			case GLFW_KEY_KP_SUBTRACT:
				exposure > 1 ? exposure /= 2 : exposure = 1;
				break;

			// Key value control:
			case GLFW_KEY_UP:
				keyValue *= 1.5f;
				break;
			case GLFW_KEY_DOWN:
				keyValue /= 1.5f;
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