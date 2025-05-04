#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform int displayMode = 0;  // 0 = position, 1 = normal

void main() {
    if (displayMode == 0) {
        vec3 pos = texture(gPosition, TexCoords).rgb;
        // Better visualization - map position range to [0,1]
        FragColor = vec4(normalize(pos) * 0.5 + 0.5, 1.0);
    } else {
        vec3 norm = texture(gNormal, TexCoords).rgb;
        FragColor = vec4(normalize(norm) * 0.5 + 0.5, 1.0);
    }
}