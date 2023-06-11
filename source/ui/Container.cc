#include <akimbo/ui/Container.hh>

namespace Akimbo
{

namespace UI
{

Widget& Container::addChild(Widget& widget)
{
	children.emplace_back(widget);
	prepare(children.back());

	return widget;
}

bool Container::Child::isPointInside(Vec2 at)
{
	return
		at.x >= position.x && at.x <= position.x + size.x &&
		at.y >= position.y && at.y <= position.y + size.y;
}

void Container::onMouseClick(Vec2 at)
{
	for(auto it : children)
	{
		if(it.isPointInside(at))
		{
			at -= it.position;
			at /= it.size;

			it.widget.onMouseClick(at);
			break;
		}
	}
}

bool Container::onMouseDrag(Vec2 at)
{
	for(auto it : children)
	{
		if(it.isPointInside(at))
		{
			at -= it.position;
			at /= it.size;

			return it.widget.onMouseDrag(at);
			break;
		}
	}

	return false;
}


}

}
