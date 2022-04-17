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
		auto& l1 = ui.add <Akimbo::UI::Label> (
			ui.left(50).then(-0.3f),
			ui.top(33).then(-0.15f),
			ui.right(50).then(-0.3f),
			ui.top(33).then(+0.15f),
			f
		);

		auto& l2 = ui.add <Akimbo::UI::TextInput> (
			ui.left(50).then(-0.3f),
			ui.bottom(33).then(+0.15f),
			ui.right(50).then(-0.3f),
			ui.bottom(33).then(-0.15f),
			f
		);

		l1.setText("Start");

		//setWidgetFocus(l1);
	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
	}

	void onKeyPress(char key) override
	{
		DBG_LOG("User defined '%c'", key);
	}

	void onRender(Akimbo::Frame& frame) override
	{
		frame.color(0, 255, 0);
		frame.drawBox(boxAt, Vec2(1.0f, 1.0f), false);
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
