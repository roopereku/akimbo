#include "akimbo/Core.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/atlas.png", 4,4)
	{
		auto& tab = ui.add<Akimbo::UI::TabbedContainer>(
				ui.left(10), ui.top(10), ui.right(10), ui.bottom(10)
		);

		// FIXME fix resize
		auto& tab1 = tab.tab("tab1");
		auto& tab2 = tab.tab("tab2");
		auto& tab3 = tab.tab("tab3");

	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}

private:
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
