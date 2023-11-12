#ifndef AKIMBO_RENDDERER_HH
#define AKIMBO_RENDDERER_HH

#include <akimbo/UpdatingEntity.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo
{

class Window;

class Renderer : public UpdatingEntity
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

	virtual void onUpdate() override = 0;

	EntityProperty <Window> window;
};

}

#endif
