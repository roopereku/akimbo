#include <akimbo/ui/Widget.hh>

namespace Akimbo
{

namespace UI
{

void Widget::onUpdate()
{
}

void Widget::onRender(Render2D& render)
{
	render.color(1.0f, 1.0f, 1.0f);
	render.clear();
}

void Widget::onResize()
{
	render();
}

void Widget::onMouseClick(Vec2i at)
{
	onMouseClick(normalizePoint(at));
}

void Widget::onMouseDrag(Vec2i at)
{
	onMouseDrag(normalizePoint(at));
}

Vec2 Widget::normalizePoint(Vec2i at)
{
	return Vec2(
		static_cast <float> (at.x) / size.x,
		static_cast <float> (at.y) / size.y
	);
}

}

}
