#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/EntityProperty.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/Renderer.hh>
#include <akimbo/View.hh>

namespace akimbo
{

class WindowContent;

class Window : public View
{
public:
	class Content;

	EntityProperty <Content> content;

	virtual Renderer& createRenderer() = 0;

	void onClick(Vec2i at) final override;
	void onDrag(Vec2i at) final override;

protected:
	Window();
	virtual ~Window();

	virtual void onResize();

	void onMouseButtonDown(Vec2i at);
	void onMouseMoved(Vec2i at);
	void onMouseButtonUp(Vec2i at);

	Renderer* renderer = nullptr;

private:
	void onPropertyChanged(Property& property) final override;

	bool mouseHeld = false;
	bool mouseMoved = false;
};

class Window::Content : public Entity, public RenderTarget2D
{
public:
	Content() : window(*this)
	{
	}

	friend class Window;

protected:
	EntityProperty <Window> window;

	virtual void onAttached() = 0;
	virtual void onMouseClick(Vec2i at) = 0;
	virtual void onMouseDrag(Vec2i at) = 0;
};

}

#endif
