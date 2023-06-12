#ifndef AKIMBO_RENDERER2D_HH
#define AKIMBO_RENDERER2D_HH

#include <akimbo/Renderer.hh>
#include <akimbo/Vector2.hh>

namespace Akimbo
{

class RenderTarget2D;
class Render2D : public Render
{
public:
	virtual void color(float r, float g, float b, float a = 1.0f) = 0;
	virtual void clear() = 0;

	virtual void box(Vec2 position, Vec2 size) = 0;
	virtual void box(Vec2i position, Vec2i size) = 0;

	virtual void target(Vec2 position, Vec2 size, RenderTarget2D& rt) = 0;
	virtual void target(Vec2i position, Vec2i size, RenderTarget2D& rt) = 0;
};

class RenderTarget2D : public RenderTarget
{
public:
	virtual void onRender(Render2D& render) {}
};

}

#endif
