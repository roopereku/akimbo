#include <akimbo/Renderer2D.hh>
#include <akimbo/Window.hh>

namespace akimbo
{

Renderer2D::Renderer2D(Window& target) : Renderer(target)
{
	addRepeatingTask([this]()
	{
		if(window)
		{
			auto& content = window.getValue().content.getValue();

			if(content.isDirty())
			{
				content.onRender(*this);
				content.clear();
			}

			display();
		}
	});
}

Vec2i Renderer2D::getOrigin()
{
	return Vec2i(0, 0);
}

}
