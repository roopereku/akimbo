#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/Renderer2D.hh>
#include <akimbo/Vector2.hh>

#include <cassert>

namespace Akimbo
{

class Window;
class WindowContent : public RenderTarget2D
{
public:
	virtual bool onMouseClick(Vec2i at) { return false; };
	virtual bool onMouseDrag(Vec2i at) { return false; };

	virtual void onResize(Vec2i size) {};

	WindowContent& operator=(WindowContent& rhs)
	{
		window = rhs.window;
		renderer = rhs.renderer;

		return *this;
	}

	bool isAttached()
	{
		return window;
	}

	friend class Window;

protected:
	Renderer& getRenderer()
	{
		assert(renderer != nullptr);
		return *renderer;
	}

	virtual void onAttached() {};

private:
	Window* window = nullptr;
	Renderer* renderer = nullptr;
};

}

#endif
