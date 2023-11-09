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

	void onRender(Renderer2D& render) override;
	void onChildAdded() override;

	Direction direction;
};

}

#endif
