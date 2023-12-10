#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/EntityProperty.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/View.hh>

namespace akimbo
{

class WindowContent;
class Renderer;

class Window : public Entity
{
public:
	class Content;
	EntityProperty <Content> content;

	virtual Renderer& createRenderer() = 0;

protected:
	Window();
	virtual ~Window();

	void onMouseButtonDown(Vec2i at);
	void onMouseMoved(Vec2i at);
	void onMouseButtonUp(Vec2i at);

	void onWindowResized(Vec2i size);

	virtual Vec2i getSize() = 0;

	Renderer* renderer = nullptr;

private:
	void onPropertyChanged(Property& property) final override;

	bool mouseHeld = false;
	bool mouseMoved = false;
};

class Window::Content : public View, public RenderTarget2D
{
public:
	Content() : window(*this)
	{
	}

	friend class Window;

protected:
	EntityProperty <Window> window;

	virtual void onAttached() = 0;

	virtual void onClick(Vec2i at) override = 0;
	virtual void onDrag(Vec2i at) override = 0;
};

}

#endif
