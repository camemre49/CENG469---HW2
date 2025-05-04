#version 330 core
layout(location=0) in vec3 inVertex;
layout(location=1) in vec3 inNormal;

uniform mat4 modelingMatrix;
uniform mat4 viewingMatrix;
uniform mat4 projectionMatrix;

out vec4 fragPosition;
out vec4 fragNormal;

void main() {
    fragPosition = modelingMatrix * vec4(inVertex, 1.0); // world-space position

    mat4 modelViewMatrix = viewingMatrix * modelingMatrix;
    mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
    fragNormal = vec4(normalMatrix * inNormal, 1.0);  // world-space normal

    gl_Position = projectionMatrix * viewingMatrix * fragPosition;
}