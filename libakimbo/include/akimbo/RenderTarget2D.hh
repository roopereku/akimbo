#ifndef AKIMBO_RENDER_TARGET_2D
#define AKIMBO_RENDER_TARGET_2D

#include <akimbo/RenderTarget.hh>
#include <akimbo/Renderer2D.hh>

namespace akimbo
{

class RenderTarget2D : public RenderTarget
{
public:
	friend class Renderer2D;

protected:
	virtual void onRender(Renderer2D& renderer) = 0;
};

}

#endif
