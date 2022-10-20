#include "akimbo/Core.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/atlas.png", 4,4), p(0, 0)
	{
		auto& c = ui.add <Akimbo::UI::Container> (
			ui.left(10), ui.top(10),
			ui.right(10), ui.bottom(10)
		);

		auto& s = c.add <Akimbo::UI::Switch> (
			c.left(5), c.top(5),
			c.left(50), c.bottom(5)
		);

		auto& t = c.add <Akimbo::UI::TabbedContainer> (
			c.right(50), c.top(5),
			c.right(5), c.bottom(5)
		);

		auto& t1 = t.tab <Akimbo::UI::Switch> ("valtteri");
		auto& t2 = t.tab <Akimbo::UI::Switch> ("iha ok");
		auto& t3 = t.tab <Akimbo::UI::Switch> ("simpsons jakso");
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
