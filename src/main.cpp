#include "../headers/globals.h"

using namespace std;

void drawScene()
{
	glBindTexture(GL_TEXTURE_2D, texture);

	for (size_t t = 0; t < 2; t++)
	{
		// Set the active program and the values of its uniform variables
		glUseProgram(gProgram[t]);
		glUniformMatrix4fv(projectionMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(viewingMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(viewingMatrix));
		glUniformMatrix4fv(modelingMatrixLoc[t], 1, GL_FALSE, glm::value_ptr(modelingMatrix));
		glUniform3fv(eyePosLoc[t], 1, glm::value_ptr(eyePos));

		glBindVertexArray(vao[t]);

		if (t == 1)
			glDepthMask(GL_FALSE);

		glDrawElements(GL_TRIANGLES, gFaces[t].size() * 3, GL_UNSIGNED_INT, 0);

		if (t == 1)
			glDepthMask(GL_TRUE);
	}
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	static float angle = 0;

	float angleRad = (float)(angle / 180.0) * M_PI;

	// Compute the modeling matrix

	//modelingMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -0.4f, -5.0f));
	//modelingMatrix = glm::rotate(modelingMatrix, angleRad, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matT = glm::translate(glm::mat4(1.0), glm::vec3(-0.5f, -0.4f, -5.0f));   // same as above but more clear
	//glm::mat4 matR = glm::rotate(glm::mat4(1.0), angleRad, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matRx = glm::rotate<float>(glm::mat4(1.0), (-90. / 180.) * M_PI, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 matRy = glm::rotate<float>(glm::mat4(1.0), (-90. / 180.) * M_PI, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 matRz = glm::rotate<float>(glm::mat4(1.0), angleRad, glm::vec3(0.0, 0.0, 1.0));
	modelingMatrix = matRy * matRx;

	// Let's make some alternating roll rotation
	static float rollDeg = 0;
	static float changeRoll = 2.5;
	float rollRad = (float)(rollDeg / 180.f) * M_PI;
	rollDeg += changeRoll;
	if (rollDeg >= 10.f || rollDeg <= -10.f)
	{
		changeRoll *= -1.f;
	}
	glm::mat4 matRoll = glm::rotate<float>(glm::mat4(1.0), rollRad, glm::vec3(1.0, 0.0, 0.0));

	// Let's make some pitch rotation
	static float pitchDeg = 0;
	static float changePitch = 0.1;
	float startPitch = 0;
	float endPitch = 90;
	float pitchRad = (float)(pitchDeg / 180.f) * M_PI;
	pitchDeg += changePitch;
	if (pitchDeg >= endPitch)
	{
		changePitch = 0;
	}
	//glm::mat4 matPitch = glm::rotate<float>(glm::mat4(1.0), pitchRad, glm::vec3(0.0, 0.0, 1.0));
	//modelingMatrix = matRoll * matPitch * modelingMatrix; // gimbal lock
	//modelingMatrix = matPitch * matRoll * modelingMatrix;   // no gimbal lock

	glm::quat q0(0, 1, 0, 0); // along x
	glm::quat q1(0, 0, 1, 0); // along y
	glm::quat q = glm::mix(q0, q1, (pitchDeg - startPitch) / (endPitch - startPitch));

	float sint = sin(rollRad / 2);
	glm::quat rollQuat(cos(rollRad / 2), sint * q.x, sint * q.y, sint * q.z);
	glm::quat pitchQuat(cos(pitchRad / 2), 0, 0, 1 * sin(pitchRad / 2));
	//modelingMatrix = matT * glm::toMat4(pitchQuat) * glm::toMat4(rollQuat) * modelingMatrix;
	modelingMatrix = matT * glm::toMat4(rollQuat) * glm::toMat4(pitchQuat) * modelingMatrix; // roll is based on pitch

	//cout << rollQuat.w << " " << rollQuat.x << " " << rollQuat.y << " " << rollQuat.z << endl;

	// Draw the scene
	drawScene();

    glDisable(GL_DEPTH_TEST);
    renderText("Test", 0, gHeight - 25, 0.6, glm::vec3(1, 1, 0));
    glEnable(GL_DEPTH_TEST);

	angle += 0.5;
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
