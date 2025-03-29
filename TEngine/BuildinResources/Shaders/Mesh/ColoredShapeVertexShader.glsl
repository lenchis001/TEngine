#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 MVP;

#include "_lightning.glsl"

out vec3 attenuationCosTheta[MAX_LIGHTS];
out vec3 attenuationCosAlpha[MAX_LIGHTS];

layout(std140) uniform PointLightsBuffer {
    PointLight lights[MAX_LIGHTS];
};

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);

	// Normal of the computed fragment, in camera space
	vec3 n = determineCameraspaceNormale();

	vec3 eyeDirectionCameraspace = determineEyeDirectionCameraspace();

	for (int i = 0; i < pointLightCount; i++) {
		PointLight light = lights[i];

		// Direction of the light (from the fragment to the light)
		vec3 l = determineLightDirection(eyeDirectionCameraspace, light.position);

		float cosTheta = determineCosTheta(l, n);
		float cosAlpha = determineCosAlpha(l, n, eyeDirectionCameraspace);
		vec3 attenuation = determineAttenuation(light);

		attenuationCosTheta[i] = attenuation * cosTheta;
		attenuationCosAlpha[i] = attenuation * pow(cosAlpha, 5);
	}

}
