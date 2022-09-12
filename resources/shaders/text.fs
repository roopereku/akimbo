#version 330 core
out vec4 FragColor;

in vec2 texUv;

uniform sampler2D textureUni;
uniform vec4 color;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, texture2D(textureUni, texUv).r) * color;
}
