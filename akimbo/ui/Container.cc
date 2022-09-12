#include "Container.hh"

namespace Akimbo::UI {

Container::Container(Core* core, Vec2 uiRadius)
{
	this->core = core;

	setConstraints(Constraint(0.0f, false), Constraint(0.0f, false), Constraint(1.0f, true), Constraint(1.0f, true));
	adjustPosition(uiRadius);
}

Container::Container()
{
	// set default color
	setBackgroundColor(0.5f, 0.5f, 0.5f, 0.5f);
}

Widget* Container::isInside(Vec2& point, Vec2& where)
{
	//	The point isn't inside this container
	if(!Widget::isInside(point, where))
		return nullptr;

	for(auto& child : children)
	{
		Vec2 normalizedParent = point;

		//	Is the point inside this child
		Widget* result = child->isInside(normalizedParent, where);
		if(result) return result;
	}

	//	The point isn't inside the children
	return this;
}

void Container::onRender(Render& render)
{
	for(auto& child : children)
		child->draw(render);
}

void Container::onUpdate(double delta)
{
	for(auto& child : children)
		child->onUpdate(delta);
}

Vec2i Container::resize(Vec2i newSize)
{
	newSize = Widget::resize(newSize);
	//DBG_LOG("Passing size (%d %d) to children for resize", newSize.x, newSize.y);

	for(auto& child : children)
	{
		child->resize(newSize);
		child->renderSelf();
	}

	//	If this is the root container, finally render it
	if(!parent)
		renderSelf();

	return newSize;
}

}
