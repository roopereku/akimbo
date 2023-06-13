#include <akimbo/ui/ScrollContainer.hh>
#include <SDL2/SDL_log.h>

#include <cmath>

namespace Akimbo::UI
{

void ScrollContainer::adjustChildren()
{
	Vec2i childOffset(0, 0);
	int part = size.x;

	for(auto& child : children)
	{
		if(child.maxSize > 0)
			child.size = Vec2(child.maxSize, size.y);

		else child.size = Vec2(part, size.y);

		child.position = childOffset;
		childOffset.x += child.size.x;
		child.widget.onResize(child.size);
	}
}

void ScrollContainer::setMaximumSize(Widget& widget, int pixels)
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

void ScrollContainer::prepare(Widget& widget)
{
	children.emplace_back(widget);
	children.back().maxSize = 0;
	adjustChildren();
}

void ScrollContainer::onRender(Render2D& render)
{
	render.color(0.3f, 0.3f, 0.3f);
	render.clear();

	Vec2i offset(scroll, 0);
	for(auto& it : children)
		render.target(it.position + offset, it.size, it.widget);
}

bool ScrollContainer::onMouseClick(Vec2i at)
{
	at.x -= scroll;
	return Container::onMouseClick(at);
}

bool ScrollContainer::onMouseDrag(Vec2i at)
{
	if(Container::onMouseDrag(at - Vec2i(scroll, 0)))
		return true;

	if(children.empty())
		return false;

	Vec2i delta = at - previousMouse;
	if(fabs(delta.x) < 10)
	{
		float oldScroll = scroll;
		scroll += delta.x;

		if(scroll > 0)
			scroll = oldScroll;
	}

	previousMouse = at;
	return true;
}

}
