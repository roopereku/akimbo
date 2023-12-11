#ifndef AKIMBO_UI_WIDGET_RENDERER__HH
#define AKIMBO_UI_WIDGET_RENDERER__HH

#include <akimbo/Vector2.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/ui/Widget.hh>

namespace akimbo::UI
{

class WidgetRenderer : public Renderer2D
{
public:
	WidgetRenderer(Renderer2D& renderer, Widget& target, Vec2i offset);

	void color(float r, float g, float b, float a = 1.0f) override;
	void setScissor(int x, int y, int w, int h) override;
	void display() override;

	void clear(float r, float g, float b, float a = 1.0f) override;
	void clear() override;

	void box(int x, int y, int w, int h, bool filled) override;
	void line(int x1, int y1, int x2, int y2) override;

	Vec2i getOrigin() final override;
	void showBorders();

private:
	Renderer2D& renderer;
	Widget& target;

	Vec2i offset;
	Vec2i origin;
};

}

#endif
