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
	Container();

	void onRender(Render& render) override;
	void onUpdate(double delta) override;

	Vec2i resize(Vec2i newSize) override;
	Widget* isInside(Vec2& point, Vec2& where) override;

	//	Function that adds a new arbitrary widget inside this container
	template <typename T, typename... Args>
	T& add(Constraint left, Constraint top, Constraint right, Constraint bottom, Args&& ...args)
	{
		/*	If some of the given constraints don't originate from this container,
		 *	negate their gaps so that they move to the inverse direction */
		if(!isRelativeConstraint(left)) left.negateGap(true);
		if(!isRelativeConstraint(top)) top.negateGap(true);
		if(!isRelativeConstraint(right)) right.negateGap(true);
		if(!isRelativeConstraint(bottom)) bottom.negateGap(true);

		//	Create a new widget of the given type and pass arbitrary parameters to it
		/*	FIXME this is a lot of unnecessary copying.
		 *	Ideally EdgeConstraints could have a constructor and a move constructor
		 *	which is then used */
		children.push_back(std::make_shared <T> (std::forward <Args> (args)...));

		//	Because C++ only let's us access protected stuff if child is a container, cast it
		Container& child = static_cast <Container&> (*children.back());
		child.setConstraints(left, top, right, bottom);

		//	This is the parent of the new widget
		child.parent = this;
		child.core = core;

		//	Update the position of the new widget according to the given constraints
		child.adjustPosition(getSize() / 2.0f);

		return static_cast <T&> (*children.back());
	}

private:
	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
