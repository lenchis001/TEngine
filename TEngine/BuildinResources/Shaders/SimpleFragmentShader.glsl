#version <shader version>

precision lowp float;

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;

void main()
{
    color = texture(textureSampler, UV);
}