#ifndef AKIMBO_RENDERER_2D_HH
#define AKIMBO_RENDERER_2D_HH

#include <akimbo/Renderer.hh>

namespace akimbo
{

class Renderer2D : public Renderer
{
public:
	virtual void color(float r, float g, float b, float a = 1.0f) = 0;
	virtual void display() = 0;

	virtual void clear(float r, float g, float b, float a = 1.0f) = 0;
	virtual void clear() = 0;

protected:
	Renderer2D(Window& target) : Renderer(target)
	{
	}

	void onUpdate() final override;
};

}

#endif
