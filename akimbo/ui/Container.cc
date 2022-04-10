#include "Container.hh"

namespace Akimbo::UI {

Container::Container(Core* core, Vec2 uiRadius)
	: Widget(core, { Constraint(0.0f, false), Constraint(0.0f, false), Constraint(1.0f, true), Constraint(1.0f, true) })
{
	adjustPosition(uiRadius);
}

Container::Container(Core* core, const EdgeConstraints& edges)
	: Widget(core, edges)
{
}

Widget* Container::isInside(Vec2 point)
{
	//	The point isn't inside this container
	if(!Widget::isInside(point))
		return nullptr;

	for(auto& child : children)
	{
		//	Is the point inside this child
		Widget* result = child->isInside(point);
		if(result) return result;
	}

	//	The point isn't inside the children
	return this;
}

void Container::onRender(Frame& frame)
{
	Widget::onRender(frame);

	for(auto& child : children)
	{
		child->Widget::onRender(frame);
		child->onRender(frame);
	}
}

void Container::adjustPosition(Vec2 uiRadius)
{
	Widget::adjustPosition(uiRadius);

	for(auto& child : children)
		child->adjustPosition(size / 2);
}

}
