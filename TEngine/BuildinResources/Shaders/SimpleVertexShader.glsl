#version <shader version>

precision lowp float;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertexPosition, 1);

    UV = vertexUV;
}