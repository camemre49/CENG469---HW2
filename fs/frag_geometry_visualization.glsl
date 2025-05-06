#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform int renderMode;
uniform vec3 eyePos;
uniform float exposure;

// Light settings
vec3 I = vec3(1.0) * exposure * 0.4;
vec3 Iamb = vec3(0.3);
vec3 kd = vec3(0.4, 0.3, 0);     // diffuse reflectance coefficient
vec3 ka = vec3(0.1, 0.1, 0.1);   // ambient reflectance coefficient
vec3 ks = vec3(0.3, 0.3, 0.3);   // specular reflectance coefficient
vec3 lightPos = vec3(5, 5, 5);   // light position in world coordinates

void main() {
    if (renderMode == 2) {
        vec3 pos = texture(gPosition, TexCoords).xyz;
        if(length(pos) < 0.0001) discard;
        // Normalize each component separately
        FragColor = vec4(normalize(vec3(pos.x + 0.5, pos.y + 0.4, pos.z + 3)), 0.4);
    }
    else if(renderMode == 3)
    {
        if(length(texture(gNormal, TexCoords).xyz) < 0.00001) discard;
        FragColor = normalize(texture(gNormal, TexCoords).xyzw);
    }
    // I should have to move these to another shader but I will not bother.
    else if (renderMode == 4 || renderMode == 5 || renderMode == 6) {
        vec3 FragPos = texture(gPosition, TexCoords).rgb;
        if(length(FragPos) < 0.0001){
            discard;
        };
        vec3 FragNormal = normalize(texture(gNormal, TexCoords).rgb);
        vec3 L = normalize(lightPos - FragPos);
        vec3 V = normalize(eyePos - FragPos);
        vec3 H = normalize(L + V);
        vec3 N = normalize(FragNormal);

        float NdotL = max(dot(N, L), 0.0);
        float NdotH = max(dot(N, H), 0.0);

        vec3 diffuseColor = I * kd * max(0, NdotL);
        vec3 specularColor = I * ks * pow(NdotH, 100.0);
        vec3 ambientColor = Iamb * ka;

        vec3 finalColor = diffuseColor + specularColor + ambientColor;

        FragColor = vec4(clamp(finalColor, 0.0, 1.0), 1.0);
    }
    else {
        discard;
    }
}