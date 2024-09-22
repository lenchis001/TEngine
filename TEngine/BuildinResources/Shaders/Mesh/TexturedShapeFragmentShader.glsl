#version 330 core

// Interpolated values from the vertex shaders
in vec3 attenuationCosTheta;
in vec3 attenuationCosAlpha5;
in vec3 lightDirectionCameraspace;
in vec2 UV;

// Output data
out vec3 color;

uniform vec3 shapeColor;
uniform sampler2D textureSampler;

void main()
{
	vec3 rawColor = texture(textureSampler, UV).rgb + shapeColor;

	// Material properties
	vec3 MaterialDiffuseColor = rawColor;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = rawColor;

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * attenuationCosTheta +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * attenuationCosAlpha5;
}