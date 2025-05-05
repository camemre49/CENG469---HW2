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
			static bool isFullScreen = false;
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
			break;

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
			case GLFW_KEY_2:
				currentRenderMode = MODELS_WORLD_POS;
				break;
			case GLFW_KEY_3:
				currentRenderMode = MODELS_WORLD_NOR;
				break;
			case GLFW_KEY_4:
				currentRenderMode = DEFERRED_RENDERING;
				break;
			case GLFW_KEY_5:
				currentRenderMode = COMPOSITE;
				break;
			case GLFW_KEY_6:
				currentRenderMode = COMPOSITE_AND_MB;
				break;
			default: ;
		}
	}
}

/**
 * Set bool and save pressed position when middle mouse is clicked
 */
bool middleMousePressed = false;
glm::vec2 lastMousePos;
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (currentRenderMode == COMPOSITE_AND_MB) {
		if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
			if (action == GLFW_PRESS) {
				middleMousePressed = true;
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				lastMousePos = glm::vec2(xpos, ypos);
			} else if (action == GLFW_RELEASE) {
				middleMousePressed = false;
			}
		}
	}
}


void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	if (middleMousePressed) {
		// Calculate mouse movement
		glm::vec2 currentMousePos(xpos, ypos);
		glm::vec2 mouseDelta = currentMousePos - lastMousePos;
		lastMousePos = currentMousePos;

		yaw += mouseDelta.x * mouseSensitivity;
		pitch -= mouseDelta.y * mouseSensitivity;

		// Constrain pitch to prevent flipping
		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		// Update viewing matrix
		updateViewMatrix();
	}
}

void setCallbacks() {
    glfwSetKeyCallback(window, keyboard);
    glfwSetWindowSizeCallback(window, reshape);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
    reshape(window, gWidth, gHeight);
}