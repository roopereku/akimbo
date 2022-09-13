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
		//	This container will be the parent of the next widget
		//	FIXME This is probably not thread safe
		setAsCurrentParent();

		//	Create a new widget of the given type and pass arbitrary parameters to it
		children.push_back(std::make_shared <T> (std::forward <Args> (args)...));

		//	Because C++ only let's us access protected stuff if child is a container, cast it
		Container& child = static_cast <Container&> (*children.back());

		prepareChild(child, left, top, right, bottom);
		return static_cast <T&> (*children.back());
	}

private:
	void prepareChild(Container& child, Constraint& l, Constraint& t, Constraint& r, Constraint& b);
	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
