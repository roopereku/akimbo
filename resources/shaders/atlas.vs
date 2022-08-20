#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;

out vec2 texUv;
uniform mat4 transform;

uniform vec2 start;
uniform vec2 end;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0f);

	vec2 uv = (end - start) * tex;
	texUv = start + uv;
}
