#include "Widget.hh"
#include "../Core.hh"

namespace Akimbo::UI
{

Widget::Widget(Core* core, const EdgeConstraints& edges)
	: core(core), edges(edges) 
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
	size = Vec2(edges.right, edges.bottom) - position;
}

}
