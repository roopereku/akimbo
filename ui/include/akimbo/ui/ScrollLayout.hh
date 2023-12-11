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

	/// Adds a new ScrollLayout.
	/// \param direction In which direction should the scrolling happen.
	/// \return The newly created ScrollLayout.
	static ScrollLayout& add(Direction direction);

	/// Adds a new vertically scrolling ScrollLayout.
	/// \return The newly created vertical ScrollLayout.
	static ScrollLayout& addVertical();

	/// Adds a new horizontally scrolling ScrollLayout.
	/// \return The newly created horizontal ScrollLayout.
	static ScrollLayout& addHorizontal();

	/// Adds a new root ScrollLayout.
	/// \param direction In which direction should the scrolling happen. Defaults to Horizontal.
	/// \return The newly created root layout.
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
