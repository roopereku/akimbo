#ifndef AKIMBO_UI_WIDGET
#define AKIMBO_UI_WIDGET

#include <akimbo/RenderTarget2D>
#include <akimbo/UpdatingEntity>

namespace akimbo::UI
{

class Widget : public RenderTarget2D, public UpdatingEntity
{
public:

protected:
	virtual void onUpdate()
	{
	}

	virtual void onRender(Renderer2D& render)
	{
	}
};

}

#endif
