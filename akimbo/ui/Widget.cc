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

void Widget::onRender(Render& render)
{
	//	If there's a background image, draw it
	if(bgImage)
	{
		//frame.drawTexture(*bgImage, position, size);
		return;
	}

	//	Is there any background color
	bool transparent = !bgAlpha || (!bgRed && !bgGreen && !bgBlue);

	//	If there is a background color, draw a filled box with that color
	if(!transparent)
	{
		render.color(bgRed, bgGreen, bgBlue);
		render.box(position, size, true);
	}

	DBG(
		render.color(1.0f, 0.0f, 0.0f);
		render.box(position, size, false);
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

void Widget::setBackgroundColor(float r, float g, float b, float a)
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

void Widget::onUpdate(double) {}
void Widget::onResize(Vec2) {}
void Widget::onMouseClick(Vec2, int) {}
void Widget::onKeyPress(char) {}
void Widget::onKeyPress(Key) {}

Constraint Widget::top(float units)
{
	return Constraint(edges.top, units, false);
}

Constraint Widget::left(float units)
{
	return Constraint(edges.left, units, false);
}

Constraint Widget::right(float units)
{
	//	Negate units so that constraint movement is right -> left
	return Constraint(edges.right, -units, false);
}

Constraint Widget::bottom(float units)
{
	//	Negate units so that constraint movement is bottom -> top
	return Constraint(edges.bottom, -units, false);
}

Constraint Widget::top(int percents)
{
	return Constraint(edges.top, static_cast <float> (percents) / 100.0f, true);
}

Constraint Widget::left(int percents)
{
	return Constraint(edges.left, static_cast <float> (percents) / 100.0f, true);
}

Constraint Widget::right(int percents)
{
	//	Negate percents so that constraint movement is right -> left
	return Constraint(edges.right, static_cast <float> (-percents) / 100.0f, true);
}

Constraint Widget::bottom(int percents)
{
	//	Negate percents so that constraint movement is bottom -> top
	return Constraint(edges.bottom, static_cast <float> (-percents) / 100.0f, true);
}

}
