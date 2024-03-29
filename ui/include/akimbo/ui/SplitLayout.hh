#ifndef AKIMBO_UI_SPLIT_LAYOUT_HH
#define AKIMBO_UI_SPLIT_LAYOUT_HH

#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/Root.hh>

#include <vector>

namespace akimbo::UI
{

class SplitLayout : public Layout
{
public:
	enum class Direction
	{
		Vertical,
		Horizontal
	};

	static SplitLayout& add(Direction direction);
	static SplitLayout& addVertical();
	static SplitLayout& addHorizontal();

	static Root& addRoot(Direction direction = Direction::Horizontal);

private:
	SplitLayout(Direction direction) : direction(direction)
	{
	}

	void onLayout() override;
	void onClick(Vec2i at) override;

	Direction direction;
};

}

#endif
