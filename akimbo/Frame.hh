#ifndef AKIMBO_FRAME_HH
#define AKIMBO_FRAME_HH

#include "Shader.hh"
#include "Render.hh"
#include "Texture.hh"
#include "Vector2.hh"
#include "Matrix4.hh"
#include "Transform.hh"

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
	Vec2 getSize();

	friend class Render;

private:
	void clearBuffers();

	Mat4 projection;
	Vec2i realSize;

	unsigned fbo = 0;
	unsigned rbo = 0;

	float horizontalRadius = 1.0f;

protected:
	//	Render::drawFrame() needs access to the texture
	unsigned texture = 0;
};

}

#endif
