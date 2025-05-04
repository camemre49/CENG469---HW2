#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform int renderMode;

// Point light definition (for now 1, can be extended)
const vec3 objectColor = vec3(0.6, 0.5, 0);

const int NUM_LIGHTS = 4;
const vec3 lightPositions[NUM_LIGHTS] = vec3[](
vec3(0.0, 2.5, -1.0),   // Light 1
vec3(0.0, 2.5, 3.0),   // Light 1
vec3(0.0, -2.0, -1.0),  // Light 2
vec3(0.0, 0.0, 2.0)    // Light 3
);

uniform vec3 eyePos;
uniform int exposure;

void main() {
    if (renderMode == 2) {
        // if(length(texture(gPosition, TexCoords).xyz) < 0.0001) discard;
        FragColor = normalize(texture(gPosition, TexCoords).xyzw);
    }
    else if(renderMode == 3)
    {
        // if(length(texture(gNormal, TexCoords).xyz) < 0.0001) discard;
        FragColor = normalize(texture(gNormal, TexCoords).xyzw);
    }
    else if (renderMode == 4 || renderMode == 5) {
        vec3 FragPos = texture(gPosition, TexCoords).xyz;
        if(length(FragPos) < 0.0001){
            discard;
        };
        vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
        vec3 ViewDir = normalize(eyePos - FragPos);
        vec3 lighting = vec3(0.0);
        vec3 lightColor = vec3(0.6, 0.6, 0.6);

        for (int i = 0; i < NUM_LIGHTS; ++i) {
            vec3 lightPos = lightPositions[i];

            vec3 LightDir = normalize(lightPos - FragPos);
            vec3 HalfDir = normalize(ViewDir + LightDir);

            float distance = length(lightPos - FragPos);
            float attenuation = 1.0 / (distance * distance);

            float diff = max(dot(Normal, LightDir), 0.0);
            float spec = pow(max(dot(Normal, HalfDir), 0.0), 32.0);

            vec3 ambient = 0.05 * lightColor;
            vec3 diffuse = diff * lightColor;
            vec3 specular = spec * lightColor;

            lighting += (ambient + diffuse + specular) * attenuation;
        }

        lighting *= objectColor;
        lighting *= exposure * 0.7;

        FragColor = vec4(lighting, 1.0);
    }
    else {
        discard;
    }
}