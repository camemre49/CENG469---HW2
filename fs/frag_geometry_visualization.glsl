#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform int displayMode = 1;  // 0 = position, 1 = normal

void main() {
    if (displayMode == 0) {
        vec3 pos = texture(gPosition, TexCoords).rgb;
        FragColor = vec4(normalize(pos), 1);
    } else {
        vec3 norm = texture(gNormal, TexCoords).rgb;
        FragColor = vec4(normalize(norm), 0.5);
    }
}