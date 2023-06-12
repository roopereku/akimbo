#ifndef AKIMBO_UI_WIDGET_HH
#define AKIMBO_UI_WIDGET_HH

#include <akimbo/WindowContent.hh>

namespace Akimbo
{

namespace UI
{

class Widget : public Akimbo::WindowContent2D
{
public:
	void onUpdate() override;

	virtual void onRender(Render2D& render) override;
};

}

}

#endif
