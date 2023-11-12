#ifndef AKIMBO_UI_LAYOUT_HH
#define AKIMBO_UI_LAYOUT_HH

#include <akimbo/ui/Widget.hh>

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

protected:
	virtual void onChildAdded() = 0;

	struct WidgetInLayout
	{
		WidgetInLayout(Widget& widget);

		std::shared_ptr <Widget> widget;
		int x = 0;
		int y = 0;
	};

	std::vector <WidgetInLayout> children;

private:
	void prepareChild(Widget& child);
};

}

#endif
