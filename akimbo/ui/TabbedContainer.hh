#ifndef AKIMBO_UI_TABBED_CONTAINER_HH
#define AKIMBO_UI_TABBED_CONTAINER_HH

#include "Container.hh"
#include "Button.hh"

namespace Akimbo::UI
{

class TabbedContainer : public Container
{
public:
	template <typename T, typename... Args>
	T& tab(const std::string& name, Args&& ...args)
	{
		Widget* widget = &add <T> (left(), top(0.1f), right(), bottom(), std::forward <Args> (args)...);
		create(widget, name);

		return static_cast <T&> (*widget);
	}

	Container& tab(const std::string& name)
	{
		return tab <Akimbo::UI::Container> (name);
	}

	void setTitleTransparency(float alpha);

	void onRender(Render& render) override;
	Widget* isInside(Vec2& point, Vec2& where) override;

private:
	void create(Widget* widget, const std::string& name);

	float titleTransparency = 0.7f;
	std::vector<std::pair<Button*, Widget*>> tabs;
	Widget* selected = nullptr;
	
};

};


#endif
