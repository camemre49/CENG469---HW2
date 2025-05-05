#include "../headers/globals.h"

void updateBlurAmountFromCameraRotation() {
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;

    // Compute angular speed (simple euclidean distance in yaw-pitch space)
    float yawDelta = yaw - previousYaw;
    float pitchDelta = pitch - previousPitch;
    float angularVelocity = sqrt(yawDelta * yawDelta + pitchDelta * pitchDelta) / static_cast<float>(deltaTime);

    // Scale and clamp to get a blur amount
    float blurFactor = glm::clamp(angularVelocity * 0.02f, 0.0f, 1.0f);
    blurFactor /= blurScale; // Scale down for smoother blur

    // Smooth it over time
    float decaySpeed = 3.0f;
    if (blurFactor > blurAmount)
        blurAmount = blurFactor;
    else
        blurAmount = glm::mix(blurAmount, blurFactor, static_cast<float>(deltaTime) * decaySpeed);

    if (blurAmount < 0.1f) {
        blurAmount = 0.0f;
    }

    // Store for next frame
    previousYaw = yaw;
    previousPitch = pitch;
    previousTime = currentTime;
}


void updateViewMatrix() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 cameraFront = glm::normalize(front);

    viewingMatrix = glm::lookAt(eyePos, eyePos + cameraFront, eyeUp);
}

void resetViewToInitial() {
    yaw = -90.0f;
    pitch = 0.0f;
    updateViewMatrix();
}