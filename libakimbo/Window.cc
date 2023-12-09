#include <akimbo/Window.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

Window::Window() : content(*this)
{
}

Window::~Window()
{
}

void Window::onPropertyChanged(Property& property)
{
	if(property == content)
	{
		content.getValue().size = getSize();
		content.getValue().window = *this;
		content.getValue().onAttached();

		content.getValue().render();
	}
}

void Window::onMouseButtonDown(Vec2i at)
{
	mouseHeld = true;
	mouseMoved = false;
}

void Window::onMouseMoved(Vec2i at)
{
	if(mouseHeld)
	{
		if(content)
		{
			content().onDrag(at);
		}
	}

	mouseMoved = true;
}

void Window::onMouseButtonUp(Vec2i at)
{
	if(mouseHeld && !mouseMoved)
	{
		if(content)
		{
			content().onClick(at);
		}
	}

	mouseHeld = false;
	mouseMoved = false;
}

}
