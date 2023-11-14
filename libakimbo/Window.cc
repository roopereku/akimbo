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

void Window::mouseButtonDown(Vec2i at)
{
	mouseHeld = true;
	mousePosition = at;
}

void Window::mouseMoved(Vec2i at)
{
	if(mouseHeld)
	{
		Vec2i delta = mousePosition - at;
		onDrag(delta);
	}

	mousePosition = at;
}

void Window::mouseButtonUp(Vec2i at)
{
	if(mouseHeld)
	{
		onClick(at);
	}

	mouseHeld = false;
	mousePosition = at;
}

void Window::onClick(Vec2i at)
{
	if(content)
	{
		content().onMouseClick(at);
	}
}

void Window::onDrag(Vec2i delta)
{
	if(content)
	{
		content().onMouseDrag(delta);
	}
}

}
