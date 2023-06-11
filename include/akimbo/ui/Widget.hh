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
	virtual void onMouseClick(Vec2 at) {};
	virtual bool onMouseDrag(Vec2 at) { return false; };

private:
	void onMouseClick(Vec2i at) override;
	void onMouseDrag(Vec2i at) override;
	void onResize() override;

	Vec2 normalizePoint(Vec2i at);
};

}

}

#endif
