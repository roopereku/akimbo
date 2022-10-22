#include "akimbo/Core.hh"
#include "akimbo/Debug.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Widget.hh"

class Overlay : public Akimbo::UI::Widget
{
public:
	void onMouseClick(Vec2, int) override
	{
		DBG_LOG("overlay clicked");
	}
};

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/cardatlas.jpg", 13,5), p(0, 0)
	{
		ui.add <Akimbo::UI::Switch> (
			ui.left(), ui.top(),
			ui.left(25), ui.top(25)
		);

		ui.add <Akimbo::UI::Switch> (
			ui.right(25), ui.top(),
			ui.right(), ui.top(25)
		);

		ui.add <Overlay> (
			ui.left(), ui.top(),
			ui.left(50), ui.bottom()
		);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}

private:
	Vec2i p;
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
