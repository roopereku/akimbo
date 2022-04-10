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

	virtual void onRender(Frame&) {};
	virtual void adjustPosition(Vec2 uiRadius);
	virtual void onResize(Vec2 resizeFactor) {};

	//	Helpers to get some constrain with a gap
	/*	FIXME
	 *
	 *	The gap could be negated for bottom and right so that when gap is 0.1f, and constraint
	 *	is right, the gap goes left instead of right */
	Constraint top(float gap, bool isPercentage) { return Constraint(edges.top, gap, isPercentage); }
	Constraint left(float gap, bool isPercentage) { return Constraint(edges.left, gap, isPercentage); }
	Constraint right(float gap, bool isPercentage) { return Constraint(edges.right, gap, isPercentage); }
	Constraint bottom(float gap, bool isPercentage) { return Constraint(edges.bottom, gap, isPercentage); }

protected:
	Core* core;
	Widget* parent = nullptr;

	Vec2 position;
	Vec2 size;

	EdgeConstraints edges;
};

}

#endif
