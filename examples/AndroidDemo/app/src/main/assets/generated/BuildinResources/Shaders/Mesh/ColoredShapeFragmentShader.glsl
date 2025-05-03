#version 300 es

precision lowp float;

out vec3 color;

uniform vec3 shapeColor;

void main()
{
	color = shapeColor;
}