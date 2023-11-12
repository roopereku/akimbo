#include <akimbo/Window.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/WidgetRenderer.hh>

namespace akimbo::UI
{

Layout::WidgetInLayout::WidgetInLayout(Widget& widget) :
	widget(std::static_pointer_cast <Widget> (widget.shared_from_this()))
{
}

void Layout::onRender(Renderer2D& render)
{
	for(auto& child : children)
	{
		WidgetRenderer renderer(render, *child.widget, child.position);
		child.widget->onRender(renderer);
	}
}

void Layout::prepareChild(Widget& child)
{
	child.parent = *this;
	children.emplace_back(child);
	onLayout();
}

}
