#version 300 es

precision lowp float;

layout (location = 0) in vec3 vertexPosition;

out vec3 TexCoords;

uniform mat4 MVP;

void main()
{
    TexCoords = vertexPosition;
    gl_Position = MVP * vec4(vertexPosition, 1.0);
}