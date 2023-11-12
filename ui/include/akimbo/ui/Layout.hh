#ifndef AKIMBO_UI_LAYOUT_HH
#define AKIMBO_UI_LAYOUT_HH

#include <akimbo/ui/Widget.hh>
#include <akimbo/Vector2.hh>

#include <vector>

namespace akimbo::UI
{

class Layout : public Widget
{
public:
	template <typename T>
	T& child(T& widget)
	{
		prepareChild(widget);
		return widget;
	}

	void onRender(Renderer2D& render) final override;
	virtual void onLayout() override = 0;

protected:
	struct WidgetInLayout
	{
		WidgetInLayout(Widget& widget);

		std::shared_ptr <Widget> widget;
		Vec2i position;
	};

	std::vector <WidgetInLayout> children;

private:
	void prepareChild(Widget& child);
};

}

#endif
