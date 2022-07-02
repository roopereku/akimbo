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
			ui.left(25),
			ui.top(25),
			ui.right(25),
			ui.bottom(25)
		);

		auto& switch1 = cont1.add <Akimbo::UI::Switch> (
			cont1.left(50).then(-0.2f),
			cont1.top(50).then(-0.2f),
			cont1.right(50).then(-0.2f),
			cont1.bottom(50).then(-0.2f)
		);

		auto& switch2 = cont1.add <Akimbo::UI::Switch> (
			switch1.right().then(0.2f),
			switch1.top(),
			switch1.right().then(0.5f),
			switch1.bottom()
		);

	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
		render();
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
		render.box(boxAt, Vec2(0.5f, 0.5f), true);
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
