#ifndef AKIMBO_RENDDERER_HH
#define AKIMBO_RENDDERER_HH

#include <akimbo/Window.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo
{

class Window;

class Renderer : public Entity
{
public:
	const EntityProperty <Window>& getWindow() const
	{
		return window;
	}

protected:
	Renderer(Window& target) : window(*this, target)
	{
	}

	Renderer(Renderer& rhs) : window(*this, rhs.window)
	{
	}

	EntityProperty <Window> window;
};

}

#endif
