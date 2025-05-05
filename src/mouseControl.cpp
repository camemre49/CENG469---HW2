#include "../headers/globals.h"

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