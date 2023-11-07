#include <akimbo/Window.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

Window::Window()
	: width(*this, 0), height(*this, 0), content(*this)
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
		content.getValue().render();
	}
}

}
