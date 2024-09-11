#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

out vec3 positionWorldspace;
out vec3 normalCameraspace;
out vec3 eyeDirectionCameraspace;
out vec3 lightDirectionCameraspace;

uniform mat4 MVP;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPosition;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);

	mat3 modelMatrix3 = mat3(modelMatrix);
	mat3 viewMatrix3 = mat3(viewMatrix);

	// Position of the vertex, in worldspace : modelMatrix * position
	positionWorldspace = modelMatrix3 * vertexPosition;

	mat3 vmMatrix = viewMatrix3 * modelMatrix3;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPositionCameraspace = vmMatrix * vertexPosition;
	eyeDirectionCameraspace = -vertexPositionCameraspace;

	// Vector that goes from the vertex to the light, in camera space. modelMatrix is ommited because it's identity.
	vec3 lightPositionCameraspace = viewMatrix3 * lightPosition;
	lightDirectionCameraspace = lightPositionCameraspace + eyeDirectionCameraspace;

	// Normal of the the vertex, in camera space
	normalCameraspace = vmMatrix * vertexNormal; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
}