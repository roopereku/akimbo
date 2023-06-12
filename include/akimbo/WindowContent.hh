#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/Renderer2D.hh>
#include <akimbo/Vector2.hh>

namespace Akimbo
{

class WindowContentBase
{
public:
	virtual bool onMouseClick(Vec2i at) { return false; };
	virtual bool onMouseDrag(Vec2i at) { return false; };

	virtual void onResize(Vec2i size) {};
};

class WindowContent2D : public WindowContentBase, public RenderTarget2D
{
public:
};

}

#endif
