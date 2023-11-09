#ifndef AKIMBO_UI_WIDGET
#define AKIMBO_UI_WIDGET

#include <akimbo/RenderTarget2D.hh>
#include <akimbo/UpdatingEntity.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo::UI
{

class Layout;

class Widget : public RenderTarget2D, public UpdatingEntity
{
public:
	virtual void onRender(Renderer2D& render);

	EntityProperty <Layout> parent;

protected:
	Widget();

	virtual void onUpdate();
};

}

#endif
