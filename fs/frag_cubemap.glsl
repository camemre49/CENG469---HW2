#version 330 core

uniform samplerCube cubemap;

in vec3 TexCoord;

out vec4 fragColor;

void main(void)
{
	fragColor = vec4(vec3(texture(cubemap, TexCoord)),1);
}
