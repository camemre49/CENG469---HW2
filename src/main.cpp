#include "../headers/globals.h"

using namespace std;

void setObjectMatrices() {
	static glm::quat rotationQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	static float rotationAngle = 0.0f;

	// Place the object to center and rotate around y axis
	rotationQuat = glm::angleAxis(rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelingMatrix = translate(glm::mat4(1.0f), glm::vec3(0, -0.4f, -3.0f)) * mat4_cast(rotationQuat);

	if (shouldMove) {
		// Increase the angle and if it exceeds 2 pi wrap.
		rotationAngle += 0.005f;
		rotationAngle = fmod(rotationAngle, glm::two_pi<float>());
	}
}

void drawScene()
{
	for (size_t t = 0; t < 2; t++)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		// Set the active program and the values of its uniform variables
		glUseProgram(gProgram[t]);
		glUniformMatrix4fv(projectionMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(viewingMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(viewingMatrix));
		glUniformMatrix4fv(modelingMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(modelingMatrix));
		glUniform3fv(eyePosLoc[t], 1, glm::value_ptr(eyePos));
		glUniform1i(glGetUniformLocation(gProgram[t], "renderMode"), currentRenderMode);

		glBindVertexArray(vao[t]);

		if (IS_CUBEMAP_PROGRAM(t)) {
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);
			glUniform1i(glGetUniformLocation(gProgram[t], "exposure"), exposure);
			glUniform1f(glGetUniformLocation(gProgram[t], "logAverageLuminance"), logAverageLuminance);
			glUniform1f(glGetUniformLocation(gProgram[t], "key"), keyValue);
			glUniform1f(glGetUniformLocation(gProgram[t], "gamma"), gammaValue);
		}

		glDrawElements(GL_TRIANGLES, gFaces[t].size() * 3, GL_UNSIGNED_INT, 0);

		if (IS_CUBEMAP_PROGRAM(t)) {
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);
		}
	}
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	setObjectMatrices();
	calculateCurrentFps();


	// Draw the scene
	drawScene();

    glDisable(GL_DEPTH_TEST);
    displayTexts();
    glEnable(GL_DEPTH_TEST);
}

void mainLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char** argv)   // Create Main Function For Bringing It All Together
{
	window = initWindow();
	setCallbacks();


	mainLoop(window); // this does not return unless the window is closed

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
