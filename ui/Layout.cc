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

Widget* Layout::findAt(Vec2i& at)
{
	// If the given position is inside some child widget, recurse into the child.
	for(auto& child : children)
	{
		if(at.x >= child.position.x && at.y >= child.position.y &&
			at.x <= child.position.x + child.widget->size().x &&
			at.y <= child.position.y + child.widget->size().y)
		{
			// Modify the location so that 0 0 matches the top left
			// corner of the current child widget.
			at.x -= child.position.x;
			at.y -= child.position.y;

			return child.widget->findAt(at);
		}
	}

	// The location didn't match any child.
	return nullptr;
}

void Layout::prepareChild(Widget& child)
{
	child.parent = *this;
	children.emplace_back(child);
	onLayout();
}

}
