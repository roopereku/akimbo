#ifndef AKIMBO_UI_TABBED_CONTAINER_HH
#define AKIMBO_UI_TABBED_CONTAINER_HH

#include <akimbo/ui/Container.hh>
#include <akimbo/ui/SplitContainer.hh>
#include <akimbo/ui/ScrollContainer.hh>

namespace Akimbo
{

namespace UI
{

class ActiveTab : public Widget
{
public:
	void set(Widget& widget);
	void onRender(Render2D& render) override;

private:
	void onMouseClick(Vec2 at) override;
	bool onMouseDrag(Vec2 at) override;

	Widget* activeWidget = nullptr;
};

class TabButton;
class TabbedContainer : public VerticallySplitContainer
{
public:
	TabbedContainer();

private:
	ScrollContainer& selector;
	ActiveTab& active;

	TabButton* previousHeader = nullptr;
	void prepare(Child& child) override;
};

}

}

#endif
