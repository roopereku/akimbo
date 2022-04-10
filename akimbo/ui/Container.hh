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

	void onRender(Frame& frame) override;
	void onUpdate(double delta) override;
	void adjustPosition(Vec2 uiRadius) override;
	Widget* isInside(Vec2 point) override;

	template <typename T, typename... Args>
	T& add(const EdgeConstraints& edges, Args&& ...args)
	{
		//	Create a new widget of the given type and pass arbitrary parameters to it
		children.push_back(std::make_shared <T> (core, edges, std::forward <Args> (args)...));

		//	Because C++ only let's us access protected stuff if child is a container, cast it
		Container& child = static_cast <Container&> (*children.back());

		//	This is the parent of the new widget
		child.parent = this;
		child.core = core;

		//	Update the position of the new widget according to the given constraints
		child.adjustPosition(size / 2);

		return static_cast <T&> (*children.back());
	}

private:
	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
