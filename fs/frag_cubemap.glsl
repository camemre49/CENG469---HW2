#version 330 core

uniform samplerCube cubemap;
in vec3 TexCoord;
out vec4 fragColor;

// Control variables
uniform int exposure;

void main(void)
{
	// Get color from texture
	vec3 hdrColor = vec3(texture(cubemap, TexCoord));

	// Apply Reinhard tonemapping
	float luminance = (hdrColor.r * 0.2126 + hdrColor.g * 0.7152 + hdrColor.b * 0.0722);
	float luminanceScaled = luminance * exposure;
	float luminanceSigmoid = luminanceScaled / (luminanceScaled + 1);
	vec3 clampedColor = clamp((luminanceSigmoid / luminance) * hdrColor, vec3(0, 0, 0), vec3(1, 1, 1));

	// Apply gamma correction and return the color
	float p = 1. / 2.2;
	fragColor = vec4(pow(clampedColor, vec3(p, p, p)), 1);
}
