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

void Window::onResize()
{
}

void Window::onPropertyChanged(Property& property)
{
	if(property == content)
	{
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
		onDrag(at);
	}

	mouseMoved = true;
}

void Window::onMouseButtonUp(Vec2i at)
{
	if(mouseHeld && !mouseMoved)
	{
		onClick(at);
	}

	mouseHeld = false;
	mouseMoved = false;
}

void Window::onClick(Vec2i at)
{
	if(content)
	{
		content().onMouseClick(at);
	}
}

void Window::onDrag(Vec2i at)
{
	if(content)
	{
		content().onMouseDrag(at);
	}
}

}
