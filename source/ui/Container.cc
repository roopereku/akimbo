#include <akimbo/ui/Container.hh>

#include <SDL2/SDL_log.h>

namespace Akimbo::UI
{

Widget& Container::addChild(Widget& widget)
{
	if(isAttached())
	{
		/* Call the assignment operator of WindowContent to
		 * copy the window and renderer of this container
		 * to the newly added widget. */
		static_cast <WindowContent&> (widget) = *this;
		widget.onAttached();
	}

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

void Container::onLoadResources()
{
	for(auto it : children)
	{
		/* Call the assignment operator of WindowContent to
		 * copy the window and renderer of this container
		 * the current child. */
		static_cast <WindowContent&> (it.widget) = *this;
		it.widget.onAttached();
	}
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
