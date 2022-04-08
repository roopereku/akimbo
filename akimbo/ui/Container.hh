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
	Container(Core* core, Vec2 cameraRadius);
	Container(Core* core, const EdgeConstraints& edges);

	void onRender(Frame& frame) override;
	void adjustPosition(Vec2 uiRadius) override;

	template <typename T, typename... Args>
	T& add(const EdgeConstraints& edges, Args&& ...args)
	{
		//	Create a new widget of the given type and pass arbitrary parameters to it
		children.push_back(std::make_shared <T> (core, edges, std::forward <Args> (args)...));
		T& child = static_cast <T&> (*children.back());

		//	This is the parent of the new widget
		child.parent = this;

		//	Update the position of the new widget according to the given constraints
		children.back()->adjustPosition(size);

		return static_cast <T&> (*children.back());
	}

private:
	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
