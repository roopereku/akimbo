#include <akimbo/ui/SplitContainer.hh>

#include <SDL2/SDL_log.h>

namespace Akimbo
{

namespace UI
{

void SplitContainer::onRender(Render2D& render)
{
	for(auto it : children)
		render.target(it.position, it.size, it.widget);
}


void SplitContainer::setMaximumSize(Widget& widget, float size)
{
	for(auto& it : children)
	{
		if(&it.widget == &widget)
		{
			it.maxSize = size;
			adjustChildren();
			break;
		}
	}
}

void SplitContainer::adjustChildren()
{
	Vec2 offset(0, 0);
	Vec2 part(1, 1);

	float& target = (direction == Split::Horizontally ? part.x : part.y);
	size_t nonLimited = children.size();

	for(auto& it : children)
		nonLimited -= it.maxSize >= 0;

	target = 1.0f / nonLimited;

	for(auto& it : children)
	{
		if(it.maxSize >= 0)
			target -= (it.maxSize / nonLimited);
	}

	for(auto& it : children)
	{
		float shift = target;

		if(it.maxSize >= 0 && target > it.maxSize)
		{
			shift = it.maxSize;

			float oldTarget = target;
			target = it.maxSize;
			it.size = part;
			target = oldTarget;
		}

		else it.size = part;

		it.position = offset;

		if(direction == Split::Horizontally)
			offset.x += shift;

		else if(direction == Split::Vertically)
			offset.y += shift;
	}
}

void SplitContainer::prepare(Child& child)
{
	child.maxSize = -1;
	adjustChildren();
}

}

}
