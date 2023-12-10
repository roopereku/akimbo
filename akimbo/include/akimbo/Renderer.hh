#ifndef AKIMBO_RENDDERER_HH
#define AKIMBO_RENDDERER_HH

#include <akimbo/EntityProperty.hh>

namespace akimbo
{

class Window;

class Renderer : public Entity
{
public:
	Window& getWindow()
	{
		return window.getValue();
	}

protected:
	Renderer(Window& target) : window(*this, target)
	{
	}

	EntityProperty <Window> window;
};

}

#endif
