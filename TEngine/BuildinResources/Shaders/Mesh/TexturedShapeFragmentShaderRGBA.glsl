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
	vec4 rawColor = texture(textureSampler, UV) + vec4(shapeColor, 0);

	// Material properties
	vec4 MaterialDiffuseColor = rawColor;
	vec4 MaterialAmbientColor = vec4(0.1, 0.1, 0.1, 1) * MaterialDiffuseColor;
	vec4 MaterialSpecularColor = rawColor;

	vec3 totalDiffuse = vec3(0);
	vec3 totalSpecular = vec3(0);

	for (int i = 0; i < pointLightCount; i++) {
		totalDiffuse += attenuationCosTheta[i];
		totalSpecular += attenuationCosAlpha[i];
	}

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * vec4(totalDiffuse, 1) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * vec4(totalSpecular, 1);
}