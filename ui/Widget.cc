#include <akimbo/ui/Widget.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/Root.hh>

#include <cstdio>

namespace akimbo::UI
{

Widget::Widget() : parent(*this)
{
}

void Widget::onRender(Renderer2D& render)
{
}

void Widget::render()
{
	if(parent)
	{
		parent.getValue().render();
	}

	RenderTarget2D::render();
}

void Widget::onUpdate()
{
}

void Widget::onPropertyChanged(Property& property)
{
	if(property == parent)
	{
	}
}

}
