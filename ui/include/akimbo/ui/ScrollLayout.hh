#ifndef AKIMBO_UI_SCROLL_LAYOUT_HH
#define AKIMBO_UI_SCROLL_LAYOUT_HH

#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/Root.hh>

#include <vector>

namespace akimbo::UI
{

class ScrollLayout : public Layout
{
public:
	enum class Direction
	{
		Vertical,
		Horizontal
	};

	ValueProperty <int> scroll;

	static ScrollLayout& add(Direction direction);
	static ScrollLayout& addVertical();
	static ScrollLayout& addHorizontal();

	static Root& addRoot(Direction direction = Direction::Horizontal);

private:
	ScrollLayout(Direction direction);

	void onLayout() override;
	void onClick(Vec2i at) override;
	void onPropertyChanged(Property& property) override;

	Direction direction;
};

}

#endif
