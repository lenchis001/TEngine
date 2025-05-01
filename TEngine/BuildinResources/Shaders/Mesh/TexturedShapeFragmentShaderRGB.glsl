<shader header>

in vec2 UV;

// Output data
out vec4 color;

uniform vec3 shapeColor;
uniform sampler2D textureSampler;

void main()
{
	color = vec4(texture(textureSampler, UV).rgb + shapeColor, 1);
}