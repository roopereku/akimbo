#include <akimbo/ui/TabLayout.hh>
#include <akimbo/ui/ScrollLayout.hh>
#include <akimbo/ui/Root.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

TabLayout::TabLayout(Type contentType)
	: selectedIndex(*this, 0), content(*this), contentType(contentType)
{
}

TabLayout& TabLayout::add(Type contentType)
{
	TabLayout& tabbed = getCore().add(new TabLayout(contentType));

	switch(contentType)
	{
		case Type::Scrolling:
		{
			tabbed.child(ScrollLayout::addHorizontal());
			break;
		}
	}

	return tabbed;
}

TabLayout& TabLayout::addScrolling()
{
	return add(Type::Scrolling);
}

Root& TabLayout::addRoot(Type contentType)
{
	auto& layout = TabLayout::add(contentType);
	auto& root = Root::add(layout);

	return root;
}

void TabLayout::prepareChild(Widget& child)
{
	// If the content layout has been set, forward the child to it.
	if(content)
	{
		content().child(child);
	}

	// If the content hasn't been set, do default handling for it.
	else
	{
		// Child is guaranteed to be a layout.
		content = static_cast <Layout&> (child);
		Layout::prepareChild(child);

		children.front().position = Vec2i(0, 0);
	}
}

void TabLayout::onLayout()
{
	content().size.assignWithoutTrigger(size());
	content().onLayout();
}

void TabLayout::onClick(Vec2i at)
{
}

void TabLayout::onPropertyChanged(Property& property)
{
	Widget::onPropertyChanged(property);

	if(property == selectedIndex)
	{
		// If the index is too high, or too low, do nothing.
		if(selectedIndex() < 0 || selectedIndex() >= content().getChildCount())
		{
			// TODO: Display a warning that an invalid index was used.
			selectedIndex.assignWithoutTrigger(previousSelected);
			return;
		}

		// How many tabs and which direction are we moving in.
		int delta = selectedIndex() - previousSelected;
		previousSelected = selectedIndex();

		// If the content is a ScrollLayout, do a scrolling animation.
		if(contentType == Type::Scrolling)
		{
			ScrollLayout& scrolling = static_cast <ScrollLayout&> (content());

			addTransitionTask([&scrolling, delta](float progress)
			{
				// At the given interval, adjust the scroll throughout the distance between tabs.
				scrolling.scroll = (scrolling.size().x * delta) * progress;
			}, 0.5);
		}
	}
}

}
