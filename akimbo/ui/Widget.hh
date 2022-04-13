#ifndef AKIMBO_UI_WIDGET_HH
#define AKIMBO_UI_WIDGET_HH

#include "Constraint.hh"
#include "../Frame.hh"

namespace Akimbo
{
	class Core;
}

namespace Akimbo::UI {

class Widget
{
public:
	Widget(Core* core, const EdgeConstraints& edges);

	//	Widgets should never be copied
	Widget(const Widget& rhs) = delete;
	Widget& operator=(const Widget& rhs) = delete;

	//	Functions that get called on each frame
	virtual void onRender(Frame& frame);
	virtual void onUpdate(double delta);

	//	Function that gets called when the user clicks this widget
	virtual void onMouseClick(Vec2, int button);

	//	Function that gets called when the widget is resized
	virtual void onResize(Vec2 resizeFactor);

	//	Function that gets called when constraints should be updated
	//	NOTE Do not override or bad stuff happens
	virtual void adjustPosition(Vec2 uiRadius);

	//	Widget background setters
	void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	void setBackgroundImage(Texture& texture);
	void removeBackgroundImage();

	//	Is a point inside this widget
	virtual Widget* isInside(Vec2 point);

	//	Helpers to get constraints relative to this widget
	/*	FIXME
	 *	The gap could be negated for bottom and right so that when gap is 0.1f, and constraint
	 *	is right, the gap goes left instead of right */
	Constraint top(float gap = 0.0f, bool isPercentage = false);
	Constraint left(float gap = 0.0f, bool isPercentage = false);
	Constraint right(float gap = 0.0f, bool isPercentage = false);
	Constraint bottom(float gap = 0.0f, bool isPercentage = false);

protected:
	Core* core;
	Widget* parent = nullptr;

	Vec2 position;
	Vec2 size;

private:
	//	Widget background stuff
	uint8_t bgRed = 0;
	uint8_t bgGreen = 0;
	uint8_t bgBlue = 0;
	uint8_t bgAlpha = 0;
	Texture* bgImage = nullptr;

	EdgeConstraints edges;
};

}

#endif
