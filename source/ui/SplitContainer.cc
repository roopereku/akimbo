#include <akimbo/ui/SplitContainer.hh>

#include <algorithm>

namespace Akimbo::UI
{

void SplitContainer::onRender(Render2D& render)
{
	render.color(0.1f, 0.1f, 0.1f);
	render.clear();

	for(auto it : children)
		render.target(it.position, it.size, it.widget);
}

void SplitContainer::setMaximumSize(Widget& widget, int pixels)
{
	for(auto& it : children)
	{
		if(&it.widget == &widget)
		{
			it.maxSize = pixels;
			adjustChildren();
			break;
		}
	}
}

void SplitContainer::adjustChildren()
{
	Vec2i offset(0, 0);
	Vec2i part = size;

	int& target = (direction == Split::Horizontally ? part.x : part.y);
	size_t nonLimited = children.size();

	for(auto& it : children)
		nonLimited -= it.maxSize > 0;

	nonLimited = std::max(nonLimited, 1UL);
	target /= nonLimited;

	for(auto& it : children)
	{
		if(it.maxSize > 0)
			target -= (it.maxSize / nonLimited);
	}

	for(auto& it : children)
	{
		it.position = offset;

		if(it.maxSize > 0 && target > it.maxSize)
		{
			int oldTarget = target;
			target = it.maxSize;
			it.size = part;
			target = oldTarget;
		}

		else it.size = part;

		if(direction == Split::Horizontally)
			offset.x += it.size.x;

		else if(direction == Split::Vertically)
			offset.y += it.size.y;

		it.widget.onResize(it.size);
	}
}

void SplitContainer::prepare(Widget& widget)
{
	children.emplace_back(widget);
	children.back().maxSize = 0;
	adjustChildren();
}

}
