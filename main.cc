#include "akimbo/Core.hh"
#include "akimbo/ui/Logger.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		Akimbo::UI::Logger& logger1 = uiRoot.add <Akimbo::UI::Logger> ({
			uiRoot.left(0.1f, false), uiRoot.top(0.1f, false), 
			uiRoot.right(-0.1f, false), uiRoot.bottom(-0.5f, false)},
			f
		);

		Akimbo::UI::Logger& logger2 = uiRoot.add <Akimbo::UI::Logger> ({
			logger1.left(0.1f, true), logger1.bottom(0.1f, false),
			uiRoot.right(-0.1f, false), uiRoot.bottom(-0.0f, false)},
			f
		);

		logger1.addMessage("This is a test message for logger1");
		logger1.addMessage("This is a second test message for logger1");

		logger2.addMessage("This is a test message for logger2");
		logger2.addMessage("This is a second test message for logger2");
	}

	void onRender(Akimbo::Frame& frame) override
	{
		return;

		frame.color(255, 255, 255);
		frame.drawLine(Vec2(-1.0f, -1.0f), Vec2(0.0f, 0.0f));

		frame.color(255, 0, 0);
		frame.drawLine(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	}

	void onUpdate(double delta) override
	{
		zoomCamera(1.0 - delta / 2);
	}

private:
	Akimbo::Texture& t;
	Akimbo::Font& f;
};

int main()
{
	Game g;
	g.start();
}
