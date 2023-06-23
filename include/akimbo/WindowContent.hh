#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/Renderer2D.hh>
#include <akimbo/Vector2.hh>

namespace Akimbo
{

class Window;
class WindowContent : public RenderTarget2D
{
public:
	virtual bool onMouseClick(Vec2i at) { return false; };
	virtual bool onMouseDrag(Vec2i at) { return false; };

	virtual void onResize(Vec2i size) {};
	virtual void onAttached() {};

	WindowContent& operator=(WindowContent& rhs)
	{
		window = rhs.window;
		renderer = rhs.renderer;

		return *this;
	}

	friend class Window;

protected:
	Renderer& getRenderer() { return *renderer; }

private:
	Window* window = nullptr;
	Renderer* renderer = nullptr;
};

}

#endif
