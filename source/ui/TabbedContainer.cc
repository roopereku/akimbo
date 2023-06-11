#include <akimbo/ui/TabbedContainer.hh>
#include <akimbo/ui/Button.hh>

#include <SDL2/SDL_log.h>

namespace Akimbo
{

namespace UI
{

class TabButton : public Button
{
public:
	TabButton(size_t index) : index(index)
	{
	}

	void onRender(Render2D& render) override
	{
		render.color(0.2f, 0.2f, 0.2f);
		render.clear();

		if(selected)
			render.color(0.8f, 0.8f, 0.8f);

		else render.color(0.5f, 0.5f, 0.5f);

		render.box(Vec2(0.05f, 0.05f), Vec2(0.9f, 0.9f));
	}

	bool selected = false;
	size_t index;
};

TabbedContainer::TabbedContainer()
	:	selector(add <ScrollContainer> (5)),
		active(add <ActiveTab> ())
{
	setMaximumSize(selector, 0.1f);
}

void TabbedContainer::prepare(Child& child)
{
	if(children.size() <= 2)
	{
		SplitContainer::prepare(child);
		return;
	}

	active.set(child.widget);
	auto& header = selector.add <TabButton> (children.size() - 1);

	header.onClick = [this](Button& button)
	{
		if(previousHeader)
			previousHeader->selected = false;

		TabButton& header = static_cast <TabButton&> (button);
		header.selected = true;

		active.set(children[header.index].widget);
		previousHeader = &header;
	};

	header.onMouseClick(Vec2());
}

void ActiveTab::set(Widget& widget)
{
	activeWidget = &widget;
}

void ActiveTab::onRender(Render2D& render)
{
	if(!activeWidget)
	{
		render.color(0.3f, 0.3f, 0.3f);
		render.clear();
	}

	else render.target(Vec2(0, 0), Vec2(1, 1), *activeWidget);
}

void ActiveTab::onMouseClick(Vec2 at)
{
	if(activeWidget)
		activeWidget->onMouseClick(at);
}

bool ActiveTab::onMouseDrag(Vec2 at)
{
	return activeWidget && activeWidget->onMouseDrag(at);
}

}

}
