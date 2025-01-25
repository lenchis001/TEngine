#version 330 core

// Interpolated values from the vertex shaders
in vec3 attenuationCosTheta;
in vec3 attenuationCosAlpha5;

// Output data
out vec4 color;

uniform vec3 shapeColor;

void main()
{
	// Material properties
	vec3 MaterialDiffuseColor = shapeColor;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = shapeColor;

	color = vec4(
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * attenuationCosTheta +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * attenuationCosAlpha5, 1);
}