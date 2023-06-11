#include <akimbo/ui/ScrollContainer.hh>
#include <SDL2/SDL_log.h>

#include <cmath>

namespace Akimbo
{

namespace UI
{

void ScrollContainer::adjustChildren()
{
	Vec2 childOffset(0, 0);
	float part = 1.0f / maxVisible;

	for(auto& child : children)
	{
		child.position = childOffset;
		child.size = Vec2(part, 1.0f);

		childOffset.x += child.size.x;
	}
}

void ScrollContainer::prepare(Child& child)
{
	adjustChildren();
}

void ScrollContainer::onRender(Render2D& render)
{
	render.color(0.3f, 0.3f, 0.3f);
	render.clear();

	Vec2 offset(scroll, 0);
	for(auto& it : children)
		render.target(it.position + offset, it.size, it.widget);
}

void ScrollContainer::onMouseClick(Vec2 at)
{
	at.x -= scroll;
	Container::onMouseClick(at);
}

bool ScrollContainer::onMouseDrag(Vec2 at)
{
	if(Container::onMouseDrag(at - Vec2(scroll, 0)))
		return true;

	if(children.empty() || children.size() <= maxVisible)
		return false;

	Vec2 delta = at - previousMouse;
	if(fabs(delta.x) < 0.1f)
	{
		float oldScroll = scroll;
		scroll += delta.x;

		SDL_Log("s %.2f wp %.2f ws %.2f", scroll, children.back().position.x, children.back().size.x);

		if(scroll > 0.0f)
			scroll = oldScroll;
	}

	previousMouse = at;
	return true;
}

}

}
