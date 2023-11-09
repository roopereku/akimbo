#ifndef AKIMBO_UI_LAYOUT_HH
#define AKIMBO_UI_LAYOUT_HH

#include <akimbo/ui/Widget.hh>

#include <vector>

namespace akimbo::UI
{

class Layout : public Widget
{
public:
	template <typename T>
	T& child(T& widget)
	{
		widget.parent = *this;
		children.emplace_back(std::static_pointer_cast <Widget> (widget.shared_from_this()));
		onChildAdded();
		return widget;
	}

protected:
	virtual void onChildAdded() = 0;

	std::vector <std::shared_ptr <Widget>> children;
};

}

#endif
