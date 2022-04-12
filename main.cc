#include "akimbo/Core.hh"
#include "akimbo/ui/Logger.hh"
#include "akimbo/ui/Switch.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		auto& switch1 = uiRoot.add <Akimbo::UI::Switch> (
			uiRoot.left(0.25f, true),
			uiRoot.top(0.4f, true),
			uiRoot.left(0.25f, true).then(0.4f, false),
			uiRoot.top(0.4f, true).then(0.5f, false)
		);

		auto& logger1 = uiRoot.add <Akimbo::UI::Logger> (
			switch1.right(0.1f, false), switch1.top(0.0f, false),
			uiRoot.right(-0.1f, false), uiRoot.bottom(-0.1f, false),
			f
		);

		switch1.onSwitch = [&logger1](bool on)
		{
			if(on) logger1.setBackgroundColor(0, 100, 0);
			else logger1.setBackgroundColor(100, 100, 100);
		};
	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
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
