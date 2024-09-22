#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUv;

out vec2 UV;
out vec3 attenuationCosTheta;
out vec3 attenuationCosAlpha5;

uniform mat4 MVP;

#include "_lightning.glsl"

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);

	// Normal of the computed fragment, in camera space
	vec3 n = determineCameraspaceNormale();

	vec3 eyeDirectionCameraspace = determineEyeDirectionCameraspace();

	// Direction of the light (from the fragment to the light)
	vec3 l = determineLightDirection(eyeDirectionCameraspace);

	float cosTheta = determineCosTheta(l, n);
	float cosAlpha = determineCosAlpha(l, n, eyeDirectionCameraspace);
	vec3 attenuation = determineAttenuation();

	attenuationCosTheta = attenuation * cosTheta;
	attenuationCosAlpha5 = attenuation * pow(cosAlpha, 5);

	// UV of the vertex. No special space for this one.
	UV = vertexUv;
}
