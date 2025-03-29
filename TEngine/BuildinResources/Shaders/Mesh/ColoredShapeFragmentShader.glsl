#version 330 core

#include "Configs/Constants.glsl"
#include "Utils/LightCountUniforms.glsl"

// Interpolated values from the vertex shaders
in vec3 attenuationCosTheta[MAX_LIGHTS];
in vec3 attenuationCosAlpha[MAX_LIGHTS];

// Output data
out vec4 color;

uniform vec3 shapeColor;

void main()
{
	// Material properties
	vec3 MaterialDiffuseColor = shapeColor;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = shapeColor;

	vec3 totalDiffuse = vec3(0);
	vec3 totalSpecular = vec3(0);

	for (int i = 0; i < pointLightCount; i++) {
		totalDiffuse += attenuationCosTheta[i];
		totalSpecular += attenuationCosAlpha[i];
	}

	color = vec4(
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * totalDiffuse +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * totalSpecular, 1);
}