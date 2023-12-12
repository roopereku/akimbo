#ifndef AKIMBO_UI_TAB_LAYOUT_HH
#define AKIMBO_UI_TAB_LAYOUT_HH

#include <akimbo/EntityProperty.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/ui/Root.hh>

namespace akimbo::UI
{

class TabLayout : public Layout
{
public:
	enum class Type
	{
		Scrolling
	};

	/// Contains the index of the currently selected tab.
	ValueProperty <int> selectedIndex;

	/// Adds a new TabLayout with the given content type.
	/// \param contentType The type of the content layout.
	/// \return The newly created TabLayout.
	static TabLayout& add(Type contentType);

	/// Adds a new TabLayout with ScrollLayout as the content.
	/// \return The newly created scrolling TabLayout.
	static TabLayout& addScrolling();

	/// Adds a new root TabLayout with the given content type.
	/// \param contentType The type of the content layout.
	/// \return The newly created Root.
	static Root& addRoot(Type contentType);

	/// Tries to go to the next tab.
	/// \return True if the transition was successful.
	bool next();

	/// Tries to go to the previous tab.
	/// \return True if the transition was successful.
	bool previous();

private:
	TabLayout(Type type);

	void prepareChild(Widget& child) override;
	void onLayout() override;
	void onClick(Vec2i at) override;
	void onPropertyChanged(Property& property) override;

	EntityProperty <Layout> content;
	int previousSelected = 0;
	Type contentType;
};

}

#endif
