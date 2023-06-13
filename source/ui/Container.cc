#include <akimbo/ui/Container.hh>

#include <SDL2/SDL_log.h>

namespace Akimbo::UI
{

Widget& Container::addChild(Widget& widget)
{
	prepare(widget);
	return widget;
}

bool Container::Child::isPointInside(Vec2i at)
{
	return
		at.x >= position.x && at.x <= position.x + size.x &&
		at.y >= position.y && at.y <= position.y + size.y;
}

void Container::onResize(Vec2i size)
{
	this->size = size;

	if(!children.empty())
		adjustChildren();
}

bool Container::onMouseClick(Vec2i at)
{
	for(auto it : children)
	{
		if(it.isPointInside(at))
			return it.widget.onMouseClick(at - it.position);
	}

	return false;
}

bool Container::onMouseDrag(Vec2i at)
{
	for(auto it : children)
	{
		if(it.isPointInside(at))
			return it.widget.onMouseDrag(at - it.position);
	}

	return false;
}

}
