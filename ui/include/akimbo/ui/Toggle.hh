#ifndef AKIMBO_UI_TOGGLE_HH
#define AKIMBO_UI_TOGGLE_HH

#include <akimbo/ui/Widget.hh>
#include <akimbo/Vector3.hh>

namespace akimbo::UI
{

class Toggle : public Widget
{
public:
	/// How long does toggling last in seconds.
	ValueProperty <double> toggleDuration;

	/// The state of the toggle. On -> true, Off -> false.
	ValueProperty <bool> toggleState;

	/// Adds a new toggle.
	/// \param on Is the toggle on by default. Defaults to false.
	/// \return The newly added toggle.
	static Toggle& add(bool on = false);

	/// Toggles the toggle.
	void toggle();

private:
	Toggle(bool on);

	void onPropertyChanged(Property& property) final override;
	void onRender(Renderer2D& render) final override;
	void onClick(Vec2i at) final override;
	void onLayout() final override;

	Vec2 switchPosition;
	Vec3 backgroundColor;
};

}

#endif
