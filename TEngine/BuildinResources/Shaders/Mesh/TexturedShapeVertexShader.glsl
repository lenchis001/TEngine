#version <shader version>

precision lowp float;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUv;

out vec2 UV;

uniform mat4 MVP;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);

	// UV of the vertex. No special space for this one.
	UV = vertexUv;
}
