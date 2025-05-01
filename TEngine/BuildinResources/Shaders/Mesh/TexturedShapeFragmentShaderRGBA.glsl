<shader header>

in vec2 UV;

// Output data
out vec4 color;

uniform vec3 shapeColor;
uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV) + vec4(shapeColor, 0);
}