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

}

}
