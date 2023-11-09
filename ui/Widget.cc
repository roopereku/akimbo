#include <akimbo/ui/Widget.hh>
#include <akimbo/ui/Layout.hh>

namespace akimbo::UI
{

Widget::Widget() : parent(*this)
{
}

void Widget::onUpdate()
{
}

void Widget::onRender(Renderer2D& render)
{
}

}
