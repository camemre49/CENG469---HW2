#version 330 core
layout(location = 0) out vec4 gPosition;
layout(location = 1) out vec4 gNormal;

in vec4 fragPosition;
in vec4 fragNormal;

void main()
{
    gPosition = fragPosition;
    gNormal = fragNormal;
}
