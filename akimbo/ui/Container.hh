#ifndef AKIMBO_UI_CONTAINER_HH
#define AKIMBO_UI_CONTAINER_HH

#include "Widget.hh"
#include "Constraint.hh"
#include "../Debug.hh"

#include <utility>
#include <memory>
#include <vector>

namespace Akimbo::UI {

class Container : public Widget
{
public:
	Container(Core* core, Vec2 uiRadius);
	Container(Core* core, const EdgeConstraints& edges);

	void onRender(Render& render) override;
	void onUpdate(double delta) override;
	void adjustPosition(Vec2 uiRadius) override;
	Widget* isInside(Vec2 point) override;

	//	Function that adds a new arbitrary widget inside this container
	template <typename T, typename... Args>
	T& add(Constraint left, Constraint top, Constraint right, Constraint bottom, Args&& ...args)
	{
		/*	If some of the given constraints don't originate from this container,
		 *	negate their gaps so that they move to the inverse direction */
		if(!isRelativeConstraint(left)) left.negateGap();
		if(!isRelativeConstraint(top)) top.negateGap();
		if(!isRelativeConstraint(right)) right.negateGap();
		if(!isRelativeConstraint(bottom)) bottom.negateGap();

		//	Create a new widget of the given type and pass arbitrary parameters to it
		/*	FIXME this is a lot of unnecessary copying.
		 *	Ideally EdgeConstraints could have a constructor and a move constructor
		 *	which is then used */
		EdgeConstraints edges { left, top, right, bottom };
		children.push_back(std::make_shared <T> (core, edges, std::forward <Args> (args)...));

		//	Because C++ only let's us access protected stuff if child is a container, cast it
		Container& child = static_cast <Container&> (*children.back());

		//	This is the parent of the new widget
		child.parent = this;
		child.core = core;

		//	Update the position of the new widget according to the given constraints
		child.adjustPosition(size / 2.0f);

		return static_cast <T&> (*children.back());
	}

private:
	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
