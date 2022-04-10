#include "akimbo/Core.hh"
#include "akimbo/ui/Logger.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		Akimbo::UI::Container& cont1 = uiRoot.add <Akimbo::UI::Container> ({
			uiRoot.left(0.1f, false), uiRoot.top(0.1f, false),
			uiRoot.right(-0.1f, false), uiRoot.top(0.5f, true)
		});

		Akimbo::UI::Logger& logger1 = uiRoot.add <Akimbo::UI::Logger> ({
			cont1.left(0.1f, false), cont1.bottom(0.0f, false),
			cont1.right(-0.1f, false), uiRoot.bottom(-0.1f, false)
			}, f
		);

		Akimbo::UI::Logger& logger2 = cont1.add <Akimbo::UI::Logger> ({
			cont1.left(0.25f, true), cont1.top(0.1f, false),
			cont1.right(-0.1f, false), cont1.bottom(-0.1f, false)
			}, f
		);

		logger1.setBackgroundColor(100, 0, 0);
		logger2.setBackgroundColor(100, 0, 100);

		logger1.addMessage("This is a test message for logger1");
		logger2.addMessage("This is a test message for logger2");
	}

	void onMouseClick(Vec2 at, int button) override
	{
		boxAt = at;
	}

	void onRender(Akimbo::Frame& frame) override
	{
		frame.color(255, 255, 255);
		frame.drawLine(Vec2(-1.0f, -1.0f), Vec2(0.0f, 0.0f));

		frame.color(255, 0, 0);
		frame.drawLine(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		frame.color(0, 255, 0);
		frame.drawBox(boxAt, Vec2(1.0f, 1.0f), false);
	}

	void onUpdate(double delta) override
	{
		//zoomCamera(1.0 - delta / 2);
		cameraPosition.x += 0.1 * delta;
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
