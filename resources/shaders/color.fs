#version 330 core
out vec4 FragColor;

in vec2 texUv;
uniform vec4 color;

void main()
{
	FragColor = color;
} 
