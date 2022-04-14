#include "Widget.hh"
#include "../Core.hh"
#include "../Debug.hh"

namespace Akimbo::UI
{

Widget::Widget(Core* core, const EdgeConstraints& edges)
	: core(core), size(1.0f, 1.0f), edges(edges)
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

void Widget::onRender(Frame& frame)
{
	//	If there's a background image, draw it
	if(bgImage)
	{
		frame.drawTexture(*bgImage, position, size);
		return;
	}

	//	Is there any background color
	bool transparent = !bgAlpha || (!bgRed && !bgGreen && !bgBlue);

	//	If there is a background color, draw a filled box with that color
	if(!transparent)
	{
		frame.color(bgRed, bgGreen, bgBlue);
		frame.drawBox(position, size, true);
	}

	DBG(
		frame.color(255, 0, 0);	
		frame.drawBox(position, size, false);
	);
}

Widget* Widget::isInside(Vec2 point)
{
	//	If the point is inside this widget, return this widget
	if(point >= position && point <= position + size)
		return this;

	return nullptr;
}

bool Widget::isRelativeConstraint(Constraint& constraint)
{
	return	edges.left.isRelative(constraint) ||
			edges.right.isRelative(constraint) ||
			edges.top.isRelative(constraint) ||
			edges.bottom.isRelative(constraint);
}

void Widget::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	bgRed = r;
	bgGreen = g;
	bgBlue = b;
	bgAlpha = a;
}

void Widget::setBackgroundImage(Texture& texture)
{
	bgImage = &texture;
}

void Widget::removeBackgroundImage()
{
	bgImage = nullptr;
}

void Widget::onUpdate(double)
{
}

void Widget::onMouseClick(Vec2, int)
{
}

void Widget::onResize(Vec2)
{
}

Constraint Widget::top(float gap, bool isPercentage)
{
	return Constraint(edges.top, gap, isPercentage);
}

Constraint Widget::left(float gap, bool isPercentage)
{
	return Constraint(edges.left, gap, isPercentage);
}

Constraint Widget::right(float gap, bool isPercentage)
{
	//	Negate gap so that constraint movement is right -> left
	return Constraint(edges.right, -gap, isPercentage);
}

Constraint Widget::bottom(float gap, bool isPercentage)
{
	//	Negate gap so that constraint movement is bottom -> top
	return Constraint(edges.bottom, -gap, isPercentage);
}

}
