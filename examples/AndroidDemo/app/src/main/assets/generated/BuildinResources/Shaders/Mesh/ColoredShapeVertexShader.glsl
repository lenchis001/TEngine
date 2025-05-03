#version 300 es

precision lowp float;

layout(location = 0) in vec3 vertexPosition;

uniform mat4 MVP;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);
}
