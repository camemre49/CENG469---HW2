#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D sceneTex;
uniform float blurAmount;

// Constants
const int samples = 4;
const float blurScaleFactor = 15.f;

void main() {
    vec2 texelSize = 1.0 / textureSize(sceneTex, 0);
    vec3 color = texture(sceneTex, TexCoords).rgb;

    vec3 accum = vec3(0.0);
    float total = 0.0;

    for (int i = -samples; i <= samples; ++i) {
        float weight = 1.0 - abs(float(i)) / float(samples);
        vec2 offset = vec2(i) * texelSize * (blurAmount) * blurScaleFactor;
        accum += texture(sceneTex, TexCoords + offset).rgb * weight;
        total += weight;
    }

    accum /= total;
    FragColor = vec4(mix(color, accum, (blurAmount)), 1.0);
}
