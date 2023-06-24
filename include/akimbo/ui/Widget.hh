#ifndef AKIMBO_UI_WIDGET_HH
#define AKIMBO_UI_WIDGET_HH

#include <akimbo/WindowContent.hh>
#include <akimbo/Font.hh>

namespace Akimbo::UI
{

class Widget : public Akimbo::WindowContent
{
public:
	virtual void onRender(Render2D& render) override;
	virtual void onLoadResources() {}

	friend class Container;

protected:
	Font defaultFont;

private:
	void onAttached() final override;
};

}

#endif
