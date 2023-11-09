#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/UpdatingEntity.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo
{

class Window;

class WindowContent : public UpdatingEntity, public RenderTarget2D
{
public:
	WindowContent() : window(*this)
	{
	}

	friend class Window;

protected:
	EntityProperty <Window> window;

private:
	void onUpdate() override
	{
	}
};

}

#endif
