#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/Renderer2D.hh>
#include <akimbo/Vector2.hh>

namespace Akimbo
{

class WindowContentBase
{
public:
	virtual void onMouseClick(Vec2i at) {};
	virtual void onMouseDrag(Vec2i at) {};

	virtual void onResize() {};

	friend class Window;

protected:
	Vec2i size;
	float aspectRatio;
};

class WindowContent2D : public WindowContentBase, public RenderTarget2D
{
public:
};

}

#endif
