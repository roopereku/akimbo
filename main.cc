#include "akimbo/Core.hh"
#include "akimbo/ui/Logger.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Label.hh"
#include "akimbo/ui/TextInput.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		auto& cont1 = ui.add <Akimbo::UI::Container> (
			ui.left(10),
			ui.top(10),
			ui.right(50),
			ui.bottom(10)
		);

		auto& cont2 = cont1.add <Akimbo::UI::Container> (
			cont1.left(10),
			cont1.top(10),
			cont1.left(50),
			cont1.bottom(10)
		);

		auto& cont3 = cont1.add <Akimbo::UI::Container> (
			cont2.right(),
			cont1.top(10),
			cont1.right(10),
			cont1.bottom(50)
		);

		auto& cont4 = cont1.add <Akimbo::UI::Container> (
			cont2.right(0.1f),
			cont3.bottom(0.1f),
			cont1.right(10),
			cont1.bottom(10)
		);

		auto& cont = ui.add <Akimbo::UI::Container> (
			cont1.right(),
			ui.top(10),
			ui.right(10),
			ui.bottom(10)
		);

		auto& cont_2 = cont.add <Akimbo::UI::Container> (
			cont.left(),
			cont.top(10),
			cont.right(),
			cont.bottom(10)
		);


	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
	}

	void onKeyPress(char key) override
	{
		DBG_LOG("User defined '%c'", key);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.0f, 0.5f, 0.5f);
		render.clear();

		render.color(1.0f, 0.0f, 0.0f);
		render.box(render.topLeft, Vec2(0.5f, 0.5f), true);
	}

	void onUpdate(double delta) override
	{
	}

private:
	Vec2 boxAt;

	Akimbo::Texture& t;
	Akimbo::Font& f;
};

int main()
{
	Game g;
	g.start();
}
