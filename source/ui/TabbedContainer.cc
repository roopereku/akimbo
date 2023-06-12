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
};

class ActiveTab : public Widget
{
public:
	void set(Widget& widget)
	{
		activeWidget = &widget;
	}

	void onRender(Render2D& render) override
	{
		if(!activeWidget)
		{
			render.color(0.3f, 0.3f, 0.3f);
			render.clear();
		}

		else render.target(Vec2(0, 0), Vec2(1, 1), *activeWidget);
	}

	void onResize(Vec2i size) override
	{
		if(activeWidget)
			activeWidget->onResize(size);
	}

	bool onMouseClick(Vec2i at) override
	{
		return activeWidget && activeWidget->onMouseClick(at);
	}

	bool onMouseDrag(Vec2i at) override
	{
		return activeWidget && activeWidget->onMouseDrag(at);
	}

	Widget* activeWidget = nullptr;
};

TabbedContainer::TabbedContainer()
	:	selector(add <ScrollContainer> ()),
		active(add <ActiveTab> ())
{
	setMaximumSize(selector, 50);
}

void TabbedContainer::onResize(Vec2i size)
{
	SplitContainer::onResize(size);

	for(auto& it : tabs)
		it.second->onResize(children.back().size);
}

void TabbedContainer::prepare(Widget& widget)
{
	if(children.size() < 2)
	{
		SplitContainer::prepare(widget);
		return;
	}

	auto& header = selector.add <TabButton> ();
	tabs.emplace(std::make_pair(&header, &widget));
	selector.setMaximumSize(header, 50);

	header.onClick = [this](Button& button)
	{
		if(previousHeader)
			previousHeader->selected = false;

		TabButton& header = static_cast <TabButton&> (button);
		header.selected = true;

		previousHeader = &header;
		active.set(*tabs[&header]);
	};

	header.onMouseClick(Vec2i());
}

}

}
