#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"

class Test : public Akimbo::Core
{
public:
	Test() : font(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		auto& cont1 = ui.add <Akimbo::UI::Container> (
			ui.left(50),
			ui.top(50),
			ui.right(0.1f),
			ui.bottom(0.1f)
		);

		cont1.add <Akimbo::UI::Switch> (
			cont1.left(50).then(-0.2f),
			cont1.top(50).then(-0.2f),
			cont1.right(50).then(-0.2f),
			cont1.bottom(50).then(-0.2f)
		);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		//render.color(1.0f, 1.0f, 1.0f);
		//render.character('x', font, render.topLeft + Vec2(0.3f, -0.3f), render.radius);
	}

private:
	Akimbo::Font& font;
};

int main()
{
	Test t;
	t.start();
}
