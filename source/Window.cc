#include <akimbo/Window.hh>

namespace Akimbo
{

void Window::setContent(WindowContent& content)
{
	content.window = this;
	content.renderer = &getRenderer();

	this->content = &content;
	content.onAttached();
	onContentSet();
}

void Window::renderContent()
{
	if(content && content->popDirty())
		getRenderer().render(*content);
}

void Window::contentMouseDrag(Vec2i at)
{
	if(content)
		content->onMouseDrag(at);
}

void Window::contentMouseClick(Vec2i at)
{
	if(content)
		content->onMouseClick(at);
}

void Window::contentResize(Vec2i size)
{
	if(content)
		content->onResize(size);
}

}
