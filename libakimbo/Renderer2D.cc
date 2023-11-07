#include <akimbo/Renderer2D.hh>
#include <akimbo/Window.hh>

namespace akimbo
{

void Renderer2D::onUpdate()
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
}

}
