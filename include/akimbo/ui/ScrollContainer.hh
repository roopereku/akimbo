#ifndef AKIMBO_UI_SCROLL_CONTAINER_HH
#define AKIMBO_UI_SCROLL_CONTAINER_HH

#include <akimbo/ui/Container.hh>

namespace Akimbo
{

namespace UI
{

class ScrollContainer : public Container
{
public:
	ScrollContainer()
	{
	}

	void setMaximumSize(Widget& widget, int pixels);

private:
	void onRender(Render2D& render) override;
	void prepare(Widget& widget) override;

	bool onMouseDrag(Vec2i at) override;
	bool onMouseClick(Vec2i at) override;

	void adjustChildren() override;

	int scroll = 0;
	Vec2i previousMouse;
};

}

}

#endif
