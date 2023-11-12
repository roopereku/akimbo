#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/EntityProperty.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/Renderer.hh>
#include <akimbo/View.hh>

#include <string_view>

namespace akimbo
{

class WindowContent;

class Window : public View
{
public:
	class Content;

	EntityProperty <Content> content;

	virtual Renderer& createRenderer() = 0;

protected:
	Window();
	virtual ~Window();

	virtual void onResize();

	Renderer* renderer = nullptr;

private:
	void onPropertyChanged(Property& property) final override;
};

class Window::Content : public UpdatingEntity, public RenderTarget2D
{
public:
	Content() : window(*this)
	{
	}

	friend class Window;

protected:
	EntityProperty <Window> window;

	virtual void onAttached() = 0;

private:
	void onUpdate() override
	{
	}
};

}

#endif
