#version 330 core

#include "Configs/Constants.glsl"
#include "Utils/LightCountUniforms.glsl"

// Interpolated values from the vertex shaders
in vec3 attenuationCosTheta[MAX_LIGHTS];
in vec3 attenuationCosAlpha[MAX_LIGHTS];
in vec2 UV;

// Output data
out vec4 color;

uniform vec3 shapeColor;
uniform sampler2D textureSampler;

void main()
{
	vec3 rawColor = texture(textureSampler, UV).rgb + shapeColor;

	// Material properties
	vec3 MaterialDiffuseColor = rawColor;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = rawColor;

	vec3 totalDiffuse = vec3(0);
	vec3 totalSpecular = vec3(0);

	for (int i = 0; i < pointLightCount; i++) {
		totalDiffuse += MaterialDiffuseColor * attenuationCosTheta[i];
		totalSpecular += MaterialSpecularColor * attenuationCosAlpha[i];
	}

	color = vec4(
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		totalDiffuse +
		// Specular : reflective highlight, like a mirror
		totalSpecular, 1);
}