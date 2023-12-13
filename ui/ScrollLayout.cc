#include <akimbo/ui/ScrollLayout.hh>
#include <akimbo/ui/Root.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

ScrollLayout::ScrollLayout(Direction direction)
	: scroll(*this, 0), direction(direction)
{
}

ScrollLayout& ScrollLayout::add(Direction direction)
{
	return getCore().add(new ScrollLayout(direction));
}

ScrollLayout& ScrollLayout::addVertical()
{
	return add(Direction::Vertical);
}

ScrollLayout& ScrollLayout::addHorizontal()
{
	return add(Direction::Horizontal);
}

Root& ScrollLayout::addRoot(Direction direction)
{
	auto& layout = ScrollLayout::add(direction);
	auto& root = Root::add(layout);

	return root;
}

void ScrollLayout::onLayout()
{
	Layout::onLayout();

	Vec2i offset = direction == Direction::Horizontal ?
		Vec2i(-scroll(), 0) : Vec2i(0, -scroll());

	for(auto& child : children)
	{
		switch(direction)
		{
			case Direction::Horizontal:
			{
				child.position = offset;
				offset.x += size().x;
				break;
			}

			case Direction::Vertical:
			{
				child.position = offset;
				offset.y += size().y;
				break;
			}
		}

		child.widget.lock()->size.assignWithoutTrigger(size());
		child.widget.lock()->onLayout();
	}
}

void ScrollLayout::onClick(Vec2i at)
{
}

void ScrollLayout::onPropertyChanged(Property& property)
{
	Widget::onPropertyChanged(property);

	if(property == scroll)
	{
		onLayout();
	}
}

}
