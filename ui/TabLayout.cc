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

bool TabLayout::next()
{
	if(selectedIndex() + 1 < content->getChildCount())
	{
		selectedIndex = selectedIndex() + 1;
		return true;
	}

	return false;
}

bool TabLayout::previous()
{
	if(selectedIndex() - 1 >= 0)
	{
		selectedIndex = selectedIndex() - 1;
		return true;
	}

	return false;
}

void TabLayout::prepareChild(Widget& child)
{
	// If the content layout has been set, forward the child to it.
	if(content)
	{
		content->child(child);
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
	Layout::onLayout();

	content->size.assignWithoutTrigger(size());
	content->onLayout();

	if(contentType == Type::Scrolling)
	{
		auto scrolling = std::static_pointer_cast <ScrollLayout> (content.getValue());
		scrolling->scroll = scrolling->size().x * selectedIndex();
	}
}

void TabLayout::onClick(Vec2i at)
{
}

void TabLayout::onPropertyChanged(Property& property)
{
	Widget::onPropertyChanged(property);

	if(property == selectedIndex)
	{
		printf("Selected index updated to %d\n", selectedIndex());

		// If the index is too high, or too low, do nothing.
		if(selectedIndex() < 0 || selectedIndex() >= content->getChildCount())
		{
			// TODO: Display a warning that an invalid index was used.
			selectedIndex.assignWithoutTrigger(previousSelected);
			printf("Reset back to %d\n", selectedIndex());
			return;
		}

		if(contentType == Type::Scrolling)
		{
			auto scrolling = std::static_pointer_cast <ScrollLayout> (content.getValue());

			addTransitionTask([scrolling, current = selectedIndex(), prev = previousSelected](float progress)
			{
				// Calculate where the origin and destination are located at.
				const int originScroll = scrolling->size().x * prev;
				const int destinationScroll = scrolling->size().x * current;

				// Moving forwards.
				if(originScroll < destinationScroll)
				{
					scrolling->scroll = originScroll + (destinationScroll - originScroll) * progress;
				}

				// Moving backwards.
				else
				{
					scrolling->scroll = originScroll - (originScroll - destinationScroll) * progress;
				}

			}, 0.5);
		}

		previousSelected = selectedIndex();
	}
}

}
