#version 330 core

uniform samplerCube cubemap;
in vec3 TexCoord;
out vec4 fragColor;

// Control variables
uniform int exposure;
uniform float logAverageLuminance;
uniform float key;
uniform float gamma;
uniform int renderMode;

void main(void)
{
	// Get color from texture
	vec3 hdrColor = vec3(texture(cubemap, TexCoord));
	hdrColor = hdrColor * exposure;

	// CUBE_ONLY
	if(renderMode == 1) {
		fragColor = vec4(hdrColor, 1);
	}

	// TONEMAPPED
	if(renderMode == 0) {
		// Apply Reinhard tonemapping
		float luminance = (hdrColor.r * 0.2126 + hdrColor.g * 0.7152 + hdrColor.b * 0.0722);
		float luminanceScaled = luminance * (key / logAverageLuminance / exposure);
		float luminanceSigmoid = luminanceScaled / (luminanceScaled + 1);
		vec3 clampedColor = clamp((luminanceSigmoid / luminance) * hdrColor, vec3(0, 0, 0), vec3(1, 1, 1));

		// Apply gamma correction and return the color
		float p = 1. / gamma;
		fragColor = vec4(pow(clampedColor, vec3(p, p, p)), 1);
	}
}
