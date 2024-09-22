// Lightweight shader for mesh rendering with lightning -----------------

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightPower;

vec3 determineAttenuation()
{
	// Position of the vertex, in worldspace : modelMatrix * position
	vec3 positionWorldspace = (modelMatrix * vec4(vertexPosition, 1)).xyz;

	// Distance to the light
	float distance = length(lightPosition - positionWorldspace);

	return (lightColor * lightPower) / (distance * distance);
}

vec3 determineCameraspaceNormale()
{
	// Normal of the the vertex, in camera space
	vec3 normalCameraspace = (viewMatrix * modelMatrix * vec4(vertexNormal, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	return normalize(normalCameraspace);
}

// Direction of the light (from the fragment to the light)
vec3 determineLightDirection(vec3 eyeDirectionCameraspace)
{
	// Vector that goes from the vertex to the light, in camera space. modelMatrix is ommited because it's identity.
	vec3 lightPositionCameraspace = (viewMatrix * vec4(lightPosition, 1)).xyz;
	vec3 lightDirectionCameraspace = lightPositionCameraspace + eyeDirectionCameraspace;

	return normalize(lightDirectionCameraspace);
}

vec3 determineEyeDirectionCameraspace()
{
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPositionCameraspace = (viewMatrix * modelMatrix * vec4(vertexPosition, 1)).xyz;
	vec3 eyeDirectionCameraspace = -vertexPositionCameraspace;

	return eyeDirectionCameraspace;
}

float determineCosAlpha(vec3 l, vec3 n, vec3 eyeDirectionCameraspace)
{
	// Eye vector (towards the camera)
	vec3 E = normalize(eyeDirectionCameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	return clamp(dot(E, R), 0, 1);
}

float determineCosTheta(vec3 l, vec3 n)
{
	return clamp(dot(n, l), 0, 1);
}

// ---------------------------------------------------------------------