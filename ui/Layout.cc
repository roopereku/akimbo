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
		WidgetRenderer renderer(render, child.widget, child.position);
		child.widget.lock()->onRender(renderer);
	}
}

void Layout::onLayout()
{
	Widget::onLayout();
}

Widget* Layout::findAt(Vec2i& at)
{
	// If the given position is inside some child widget, recurse into the child.
	for(auto& child : children)
	{
		auto childWidget = child.widget.lock();
		const auto childSize = childWidget->size();

		if(at.x >= child.position.x && at.y >= child.position.y &&
			at.x <= child.position.x + childSize.x &&
			at.y <= child.position.y + childSize.y)
		{
			// Modify the location so that 0 0 matches the top left
			// corner of the current child widget.
			at.x -= child.position.x;
			at.y -= child.position.y;

			return childWidget->findAt(at);
		}
	}

	// The location didn't match any child.
	return nullptr;
}

size_t Layout::getChildCount()
{
	return children.size();
}

void Layout::prepareChild(Widget& child)
{
	child.parent = *this;
	children.emplace_back(child);
	onLayout();
}

}
