#include "akimbo/Core.hh"
#include "akimbo/Debug.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Widget.hh"

class Overlay : public Akimbo::UI::Widget
{
public:
	Overlay() : point(0.0f, 0.0f)
	{
		setBackgroundColor(0.5f, 0.5f, 0.0f, 0.5f);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.0f, 0.0f, 1.0f, 1.0f);
		render.box(point, Vec2(0.2f, 0.2f), true);
	}

	Vec2 point;
};

class Test : public Akimbo::Core
{
public:
	Test()
	{
		auto& tabs = ui.add <Akimbo::UI::TabbedContainer> (
			ui.left(25), ui.top(25),
			ui.right(25), ui.bottom(25)
		);

		auto& b = tabs.tab <Akimbo::UI::Button> ("button1");
		b.onClick = [&tabs]()
		{
			tabs.tab <Akimbo::UI::Switch> ("abc");
		};
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}
};

int main()
{
	Test t;
	t.start();
}
