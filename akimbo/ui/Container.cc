#include "Container.hh"

namespace Akimbo::UI {

Container::Container(Core* core, Vec2 cameraRadius)
	: Widget(core, {})
{
	//	Since this constructor creates a root container, make it fill the entire screen
	edges.left = Constraint(0.0f, false);
	edges.top = Constraint(0.0f, false);
	edges.right = Constraint(edges.left, 1.0f, true);
	edges.bottom = Constraint(edges.top, 1.0f, true);

	adjustPosition(cameraRadius);
}

Container::Container(Core* core, const EdgeConstraints& edges)
	: Widget(core, edges)
{
}

void Container::onRender(Frame& frame)
{
	frame.color(255, 0, 0);
	frame.drawBox(position, size, false);

	for(auto& child : children)
		child->onRender(frame);
}

void Container::adjustPosition(Vec2 uiRadius)
{
	Widget::adjustPosition(uiRadius);

	for(auto& child : children)
		child->adjustPosition(uiRadius);
}

}
