#include <akimbo/ui/SplitLayout.hh>
#include <akimbo/ui/Root.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

SplitLayout& SplitLayout::add(Direction direction)
{
	return getCore().add(new SplitLayout(direction));
}

SplitLayout& SplitLayout::addVertical()
{
	return add(Direction::Vertical);
}

SplitLayout& SplitLayout::addHorizontal()
{
	return add(Direction::Horizontal);
}

Root& SplitLayout::addRoot(Direction direction)
{
	auto& layout = SplitLayout::add(direction);
	auto& root = Root::add(layout);

	return root;
}

void SplitLayout::onLayout()
{
	if(children.empty())
	{
		return;
	}

	int refSize = direction == Direction::Horizontal ? size().x : size().y;
	int partition = refSize / children.size();
	int offset = 0;

	for(auto& child : children)
	{
		switch(direction)
		{
			case Direction::Horizontal:
			{
				child.position = Vec2i(offset, 0);
				child.widget->size.assignWithoutTrigger(Vec2i(partition, size().y));
				break;
			}

			case Direction::Vertical:
			{
				child.position = Vec2i(0, offset);
				child.widget->size.assignWithoutTrigger(Vec2i(size().x, partition));
				break;
			}
		}

		child.widget->onLayout();
		offset += partition;
	}
}

void SplitLayout::onClick(Vec2i at)
{
}

}
