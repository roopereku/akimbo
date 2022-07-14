#include "Widget.hh"
#include "../Core.hh"
#include "../Debug.hh"

namespace Akimbo::UI
{

Widget::Widget(Core* core, const EdgeConstraints& edges)
	: core(core), edges(edges)
{
	static int ids = 0;
	ids++;

	id = ids;
	DBG_LOG("Creating widget %d", id);
}

void Widget::adjustPosition(Vec2 parentRadius)
{
	//	Update the position of each constrain
	edges.top.updatePosition(parentRadius.y);
	edges.left.updatePosition(parentRadius.x);
	edges.right.updatePosition(parentRadius.x);
	edges.bottom.updatePosition(parentRadius.y);

	position = Vec2(edges.left, edges.top);
	size = Vec2(edges.right, edges.bottom) - position;

	position.y = -position.y;

	//	Do resizing if necessary
	//onResize();
}

Vec2i Widget::resize(Vec2i newSize)
{
	float parentRadius = static_cast <float> (newSize.x) / newSize.y;
	adjustPosition(Vec2(parentRadius, 1.0f));

	/*	Frame resize needs a size that's in pixels. Now that we know
	 *	how large the widget is based on the constraints, we can multiply the
	 *	parent size in pixels with a normalized version of the widget size in units */
	newSize.x = newSize.x * (size.x / parentRadius / 2);
	newSize.y = newSize.y * (size.y / 2);

	frame.resize(newSize);
	return newSize;
}

void Widget::renderSelf()
{
	//DBG_LOG("Widget %d render", id);
	Render render = frame.render();

	Widget::onRender(render);
	onRender(render);

}

void Widget::render()
{
	renderSelf();

	if(parent)
	{
		//DBG_LOG("Widgget %d renders parent", id);
		parent->render();
	}
}

void Widget::draw(Render& render)
{
	//DBG_LOG("Drawing widget %d at (%.2f %.2f) with size (%.2f %.2f)", id, position.x, position.y, size.x, size.y);
	render.frame(frame, position, size);
}

void Widget::draw()
{
	frame.draw();
}

void Widget::onRender(Render& render)
{
	render.color(bgRed, bgGreen, bgBlue, bgAlpha);

	if(bgImage) render.texture(*bgImage, render.topLeft, render.radius * 2.f);
	else render.clear();
}

Widget* Widget::isInside(Vec2& point, Vec2& where)
{
	if(parent)
	{
		/*	Because point will be a normalized point that corresponds to
		 *	a position in the parent frame, we need to convert it to a
		 *	normalized position that corresponds to a
		 *	position in this widget's frame	*/

		/*	We need to know how far the point is from the top left corner
		 *	of this widget in the paren't widget's space */
		Vec2 insideParent = parent->frame.pointAt(point);
		point = (insideParent - position);

		/*	Now that we know where the point is relative to this widget,
		 *	let's normalize it so that we can use Frame::pointAt() to
		 *	figure out where the point is inside this widget's frame */
		point.x = (point.x / (size.x)) * 2.0f - 1.0f;
		point.y = (point.y / size.y) * 2.0f + 1.0f;
	}

	//	If the position is out of bounds, it's not inside this widget
	if(point.x < -1.0f || point.y > 1.0f || point.x > 1.0f || point.y < -1.0f)
		return nullptr;

	//	Let's figure out where the normalized point is inside this widget's frame
	//	FIXME We should call pointAt only for the widget that was clicked and not it's parents
	where = frame.pointAt(point);
	return this;
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
