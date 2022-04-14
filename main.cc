#include "akimbo/Core.hh"
#include "akimbo/ui/Logger.hh"
#include "akimbo/ui/Switch.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		auto& cont1 = ui.add <Akimbo::UI::Container> (
			ui.left().then(0.1f, true),
			ui.top().then(0.1f, true),
			ui.right().then(0.1f, true),
			ui.bottom().then(0.1f, true)
		);

		auto& cont2 = cont1.add <Akimbo::UI::Container> (
			cont1.left(0.1f, false),
			cont1.top(0.1f, false),
			cont1.left(0.5f, true),
			cont1.bottom(0.1f, false)
		);

		auto& cont3 = cont1.add <Akimbo::UI::Container> (
			cont2.right(),
			cont2.top(),
			cont1.right(0.1f, false),
			cont2.bottom()
		);

		auto& switch1 = cont2.add <Akimbo::UI::Switch> (
			cont2.left(0.5f, true).then(-0.3f),
			cont2.top(0.5f, true).then(-0.3f),
			cont3.left(0.2f, false),
			cont2.bottom(0.5f, true).then(-0.3f)
		);

		cont1.setBackgroundColor(0, 0, 100);
		cont2.setBackgroundColor(100, 0, 0);
		cont3.setBackgroundColor(100, 100, 0);
	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
	}

	void onRender(Akimbo::Frame& frame) override
	{
		//frame.color(0, 255, 0);
		//frame.drawBox(boxAt, Vec2(1.0f, 1.0f), false);
	}

	void onUpdate(double delta) override
	{
		//zoomCamera(1.0 - delta / 2);
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
