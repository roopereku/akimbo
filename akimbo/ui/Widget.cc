#include "Widget.hh"
#include "../Core.hh"

namespace Akimbo::UI
{

Widget::Widget(Core* core, const EdgeConstraints& edges)
	: core(core), edges(edges), size(1.0f, 1.0f)
{
}

void Widget::adjustPosition(Vec2 uiRadius)
{
	//	Update the position of each constrain
	edges.top.updatePosition(uiRadius.y);
	edges.left.updatePosition(uiRadius.x);
	edges.right.updatePosition(uiRadius.x);
	edges.bottom.updatePosition(uiRadius.y);

	//	Calculate the position and size of the widget
	position = Vec2(edges.left, edges.top);
	Vec2 newSize = Vec2(edges.right, edges.bottom) - position;

	//	How mcuh did the widget size change
	Vec2 relation = size / newSize;
	size = newSize;

	//	Do resizing if necessary
	onResize(relation);
}

}
