#ifndef AKIMBO_FRAME_HH
#define AKIMBO_FRAME_HH

#include "Shader.hh"
#include "Render.hh"
#include "Texture.hh"
#include "Vector2.hh"
#include "Matrix4.hh"
#include "Transform.hh"

#include <functional>

namespace Akimbo {
class Frame
{
public:
	Frame();
	~Frame();

	void draw();
	void resize(Vec2i size);

	Render render();

	Transform transform;

private:
	void clearBuffers();

	Shader shader;
	Mat4 projection;

	unsigned fbo = 0;
	unsigned rbo = 0;
	unsigned texture = 0;

	float horizontalRadius = 1.0f;
};

}

#endif
