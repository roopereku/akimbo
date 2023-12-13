#include <akimbo/Renderer2D.hh>
#include <akimbo/Window.hh>

namespace akimbo
{

Renderer2D::Renderer2D(Window& target) : Renderer(target)
{
	addRepeatingTask([this]()
	{
		if(window && window->content)
		{
			auto& content = window->content;

			if(content->isDirty())
			{
				content->onRender(*this);
				content->clear();
			}

			display();
		}
	});


}

Renderer2D::Renderer2D(Renderer2D& rhs) : Renderer(rhs)
{
}

Vec2i Renderer2D::getOrigin()
{
	return Vec2i(0, 0);
}

}
