#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform int displayMode = 1;  // 0 = position, 1 = normal

void main() {
    if (displayMode == 0) {
        FragColor = normalize(texture(gPosition, TexCoords).xyzw);
    } else {
        FragColor = normalize(texture(gNormal, TexCoords).xyzw);
    }
}