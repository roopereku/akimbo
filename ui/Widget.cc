#include <akimbo/ui/Widget.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/Root.hh>

namespace akimbo::UI
{

Widget::Widget() : parent(*this)
{
}

void Widget::onRender(Renderer2D& render)
{
}

void Widget::onDrag(Vec2i at)
{
}

void Widget::onClick(Vec2i at)
{
}

void Widget::onLayout()
{
	render();
}

Widget* Widget::findAt(Vec2i& at)
{
	return this;
}

void Widget::render()
{
	if(parent)
	{
		parent->render();
	}

	RenderTarget2D::render();
}

void Widget::onPropertyChanged(Property& property)
{
	// Did the size of this widget change?
	if(property == size)
	{
		// If this widget has a parent layout, make it rearrange its children.
		if(parent)
		{
			parent->onLayout();
		}

		// If this widget has no parent layout, this should be a root layout.
		else
		{
			onLayout();
		}
	}
}

}
