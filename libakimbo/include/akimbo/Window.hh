#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include <akimbo/ValueProperty.hh>
#include <akimbo/EntityProperty.hh>
#include <akimbo/UpdatingEntity.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/Renderer.hh>

#include <string_view>

namespace akimbo
{

class WindowContent;

class Window : public UpdatingEntity
{
public:
	class Content;

	ValueProperty <unsigned> width;
	ValueProperty <unsigned> height;
	EntityProperty <Content> content;

	virtual Renderer& createRenderer() = 0;

protected:
	Window();
	virtual ~Window();

	virtual void onResize();
	virtual void onUpdate() override = 0;

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

private:
	void onUpdate() override
	{
	}
};

}

#endif
