#version 330 core
layout(location=0) in vec3 inVertex;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec3 inTexture;

uniform mat4 modelingMatrix;
uniform mat4 viewingMatrix;
uniform mat4 projectionMatrix;

out vec3 fragPosition;
out vec3 fragNormal;

void main() {
    vec4 worlPos = modelingMatrix * vec4(inVertex, 1.0);
    fragPosition = worlPos.xyz; // world-space position

    mat3 normalMatrix = transpose(inverse(mat3(modelingMatrix)));
    fragNormal = normalMatrix * inNormal;  // world-space normal

    gl_Position = projectionMatrix * viewingMatrix * worlPos;
}