#ifndef AKIMBO_UI_TABBED_CONTAINER_HH
#define AKIMBO_UI_TABBED_CONTAINER_HH

#include <akimbo/ui/Container.hh>
#include <akimbo/ui/SplitContainer.hh>
#include <akimbo/ui/ScrollContainer.hh>

#include <unordered_map>

namespace Akimbo
{

namespace UI
{

class TabButton;
class ActiveTab;

class TabbedContainer : public VerticallySplitContainer
{
public:
	TabbedContainer();

private:
	void prepare(Widget& widget) override;
	void onResize(Vec2i size) override;

	ScrollContainer& selector;
	ActiveTab& active;

	TabButton* previousHeader = nullptr;
	std::unordered_map <TabButton*, Widget*> tabs;
};

}

}

#endif
