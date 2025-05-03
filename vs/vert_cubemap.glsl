#version 330 core

uniform mat4 viewingMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 inVertex;

out vec3 TexCoord;

void main() {
	TexCoord = inVertex;  // Use vertex position as texture coordinate

	// Remove translation from view matrix (only keep rotation)
	mat4 viewWithoutTranslation = mat4(mat3(viewingMatrix));

	// Calculate position
	vec4 pos = projectionMatrix * viewWithoutTranslation * vec4(inVertex, 1.0);

	// Force depth to maximum value (1.0) by setting z = w
	gl_Position = pos.xyww;
}