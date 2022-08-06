#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;

out vec2 texUv;
uniform mat4 transform;

uniform vec2 tileOffset;
uniform vec2 tileSize;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0f);

	vec2 to = vec2(tileOffset.x, 1.0f - tileOffset.y);
	texUv = to + (tileSize * tex) + vec2(0.0f, 1.0 - tileSize.y);
}
