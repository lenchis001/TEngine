#version 330 core

// Interpolated values from the vertex shaders
in vec3 attenuationCosTheta;
in vec3 attenuationCosAlpha;
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

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * vec4(attenuationCosTheta, 1) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * vec4(attenuationCosAlpha, 1);
}