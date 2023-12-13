#ifndef AKIMBO_RENDERER_2D_HH
#define AKIMBO_RENDERER_2D_HH

#include <akimbo/Renderer.hh>

namespace akimbo
{

class Renderer2D : public Renderer
{
public:
	virtual void color(float r, float g, float b, float a = 1.0f) = 0;
	virtual void setScissor(int x, int y, int w, int h) = 0;
	virtual void display() = 0;

	virtual void clear(float r, float g, float b, float a = 1.0f) = 0;
	virtual void clear() = 0;

	virtual void box(int x, int y, int w, int h, bool filled = true) = 0;
	virtual void line(int x1, int y1, int x2, int y2) = 0;

	virtual Vec2i getOrigin();

protected:
	Renderer2D(Window& target);
	Renderer2D(Renderer2D& rhs);
};

}

#endif
