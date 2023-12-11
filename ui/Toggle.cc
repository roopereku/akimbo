#include <akimbo/ui/Toggle.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

Toggle& Toggle::add(bool on)
{
	return getCore().add(new Toggle(on));
}

Toggle::Toggle(bool on)
	: toggleDuration(*this, 0.3), toggleState(*this, std::move(on)), backgroundColor(0.3f, 0.3f, 0.3f)
{
}

void Toggle::toggle()
{
	toggleState = !toggleState();
}

void Toggle::onRender(Renderer2D& render)
{
	render.clear(backgroundColor.x, backgroundColor.y, backgroundColor.z);

	render.color(1.0f, 1.0f, 1.0f);
	render.box(switchPosition.x, switchPosition.y, size().x / 2, size().y);
}

void Toggle::onClick(Vec2i at)
{
	toggle();
}

void Toggle::onLayout()
{
	switchPosition.x = size().x * (toggleState() ? 0.5f : 0.0f);
	render();
}

void Toggle::onPropertyChanged(Property& property)
{
	Widget::onPropertyChanged(property);

	if(property == toggleState)
	{
		addTransitionTask([this](float progress)
		{
			// If the toggle is on, go from gray to green.
			if(toggleState())
			{
				// 0.3 -> 1.0.
				backgroundColor.g = 0.3f + (0.7f * progress);

				// 0.0 -> 0.5.
				float positionX = 0.5f * progress;
				switchPosition.x = size().x * positionX;
			}

			// If the toggle is off, go from green to gray.
			else
			{
				// 1.0 -> 0.3.
				backgroundColor.g = 1.0f - (0.7f * progress);

				// 0.5 -> 0.0.
				float positionX = 0.5f - (0.5f * progress);
				switchPosition.x = size().x * positionX;
			}

			render();		

		}, toggleDuration());
	}
}

}
