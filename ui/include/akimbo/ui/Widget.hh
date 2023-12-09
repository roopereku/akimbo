#ifndef AKIMBO_UI_WIDGET
#define AKIMBO_UI_WIDGET

#include <akimbo/View.hh>
#include <akimbo/RenderTarget2D.hh>
#include <akimbo/EntityProperty.hh>

namespace akimbo::UI
{

class Layout;
class WidgetRenderer;

class Widget : public View, public RenderTarget2D
{
public:
	EntityProperty <Layout> parent;

	virtual void onRender(Renderer2D& render) override;
	virtual void onDrag(Vec2i at) override;
	virtual void onClick(Vec2i at) override;
	virtual void onLayout();

	/// Find a widget at the given coordinates. This function is primarily used
	/// by Layout to find child widgets at given coordinates.
	/// \param at Coordinates to find a widget from.
	/// \returns Widget at given coordinats.
	virtual Widget* findAt(Vec2i& at);

protected:
	Widget();

	void render();
	virtual void onPropertyChanged(Property& property) override;
};

}

#endif
