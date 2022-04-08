#include "akimbo/Core.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
		Akimbo::UI::Container& atTop = uiRoot.add <Akimbo::UI::Container> ({
			uiRoot.left(0.1f, false), uiRoot.top(0.1f, false), 
			uiRoot.right(-0.3f, false), uiRoot.top(0.3f, false)
		});

		Akimbo::UI::Container& atBottom = uiRoot.add <Akimbo::UI::Container> ({
			uiRoot.left(0.1f, false), uiRoot.bottom(-0.3f, false), 
			uiRoot.left(0.3f, false), uiRoot.bottom(-0.1f, false)
		});

		Akimbo::UI::Container& underTop = uiRoot.add <Akimbo::UI::Container> ({
			atTop.right(0.0f, false), atTop.bottom(0.0f, false), 
			atTop.right(0.2f, false), atBottom.top(0.0f, false)
		});

		(void)underTop;
	}

	void onRender(Akimbo::Frame& frame) override
	{
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
