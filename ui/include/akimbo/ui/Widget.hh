#ifndef AKIMBO_UI_WIDGET
#define AKIMBO_UI_WIDGET

#include <akimbo/RenderTarget2D.hh>
#include <akimbo/UpdatingEntity.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo::UI
{

class Layout;
class WidgetRenderer;

class Widget : public UpdatingEntity, public RenderTarget2D
{
public:
	EntityProperty <Layout> parent;

	virtual void onRender(Renderer2D& render) override;

protected:
	Widget();

	void render();
	virtual void onUpdate() override;
	virtual void onPropertyChanged(Property& property) override;
};

}

#endif
