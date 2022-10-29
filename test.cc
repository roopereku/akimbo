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
	Test() :
		c1(ui.add <Akimbo::UI::Container> (ui.left(10), ui.top(25), ui.right(10), ui.bottom(25))),
		c2(c1.add <Akimbo::UI::Container> (c1.left(25), c1.top(25), c1.right(25), c1.bottom(25))),
		o(c2.add <Overlay> (c2.left(25), c2.top(25), c2.right(25), c2.bottom(25)))
	{
		c2.setBackgroundColor(0.0f, 0.0f, 0.1f, 0.1f);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		Vec2 at = o.getRealPosition(o.point, ui);

		render.color(0.5f, 0.0f, 0.0f);
		render.box(at, Vec2(0.2f, 0.2f), true);
	}

private:
	Akimbo::UI::Container& c1;
	Akimbo::UI::Container& c2;
	Overlay& o;
};

int main()
{
	Test t;
	t.start();
}
