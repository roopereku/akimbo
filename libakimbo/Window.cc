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

}
