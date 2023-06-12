#include <akimbo/Window.hh>

namespace Akimbo
{

void Window::setContent(WindowContent2D& content)
{
	contentType = ContentType::Content2D;
	this->content = &content;

	onContentSet();
}

void Window::renderContent(Renderer& renderer)
{
	if(!content)
		return;

	switch(contentType)
	{
		case ContentType::Content2D:
			WindowContent2D& content2D = (static_cast <WindowContent2D&> (*content));

			if(content2D.popDirty())
				renderer.render(content2D);
		break;
	}
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
