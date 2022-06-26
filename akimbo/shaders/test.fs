#version 330 core
out vec4 FragColor;

in vec2 texUv;

uniform sampler2D textureUni;

void main()
{
	FragColor = texture(textureUni, texUv);
} 
