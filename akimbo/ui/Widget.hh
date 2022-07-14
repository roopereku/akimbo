#ifndef AKIMBO_UI_WIDGET_HH
#define AKIMBO_UI_WIDGET_HH

#include "../KeyboardState.hh"
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

	void render();
	void renderSelf();

	void draw();
	void draw(Render& render);

	virtual void onRender(Render& render);
	virtual void onUpdate(double delta);

	//	Function that gets called when the user clicks this widget
	virtual void onMouseClick(Vec2, int button);

	//	Function that gets called when a key is pressed while this widget is active
	virtual void onKeyPress(char key);
	virtual void onKeyPress(Key key);

	//	Function that gets called when the widget is resized
	virtual void onResize(Vec2 resizeFactor);

	//	Function that gets called when constraints should be updated
	//	NOTE Do not override or bad stuff happens
	virtual Vec2i resize(Vec2i newSize);
	void adjustPosition(Vec2 parentRadius);

	//	Widget background setters
	void setBackgroundColor(float r, float g, float b, float a = 1.0f);
	void setBackgroundImage(Texture& texture);
	void removeBackgroundImage();

	//	Is a point inside this widget
	virtual Widget* isInside(Vec2& point, Vec2& where);

	//	Helpers to get constraints relative to this widget with units
	Constraint top(float units = 0.0f);
	Constraint left(float units = 0.0f);
	Constraint right(float units = 0.0f);
	Constraint bottom(float units = 0.0f);

	//	Helpers to get constraints relative to this widget with percents
	Constraint top(int percents);
	Constraint left(int percents);
	Constraint right(int percents);
	Constraint bottom(int percents);

protected:
	bool isRelativeConstraint(Constraint& constraint);

	Vec2 getSize();

	Core* core;
	Widget* parent = nullptr;

	int id;

private:
	//	Widget background stuff
	float bgRed = 0;
	float bgGreen = 0;
	float bgBlue = 0;
	float bgAlpha = 0;
	Texture* bgImage = nullptr;

	EdgeConstraints edges;
	Frame frame;

	Vec2 position;
	Vec2 size;

};

}

#endif
