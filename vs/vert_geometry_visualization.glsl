#version 330 core
layout(location = 0) in vec3 inVertex;  // Quad vertex positions
layout(location = 1) in vec2 inTexCoords; // Quad texture coordinates

out vec2 TexCoords;

void main()
{
    TexCoords = inTexCoords;
    gl_Position = vec4(inVertex, 1.0);
}
