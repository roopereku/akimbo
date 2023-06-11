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
	ScrollContainer(size_t maxVisible)
		: maxVisible(maxVisible)
	{
	}

private:
	void onRender(Render2D& render) override;
	void prepare(Child& child) override;
	bool onMouseDrag(Vec2 at) override;
	void onMouseClick(Vec2 at) override;

	void adjustChildren();

	float scroll = 0;
	size_t maxVisible;
	Vec2 previousMouse;
};

}

}

#endif
