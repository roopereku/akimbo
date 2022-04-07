#include "akimbo/Core.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core(), t(loadTexture("test.png")), f(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
	}

	void onRender(Akimbo::Frame& frame) override
	{
		frame.color(255, 255, 255);
		frame.drawLine(Vec2(-1.0f, -1.0f), Vec2(0.0f, 0.0f));

		frame.color(255, 0, 0);
		frame.drawLine(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		frame.color(255, 0, 0);
		frame.drawTexture(t, Vec2(-0.25f, -0.25f), Vec2(0.5f, 0.5f));

		frame.color(0, 255, 0);
		frame.drawBox(Vec2(-0.75f, -0.75f), Vec2(0.25f, 0.25f), false);
		frame.drawText("moi\n12345", f, Vec2(-0.75f, -0.75f), Vec2(0.25f, 0.25f));
	}

	void onUpdate(double delta) override
	{
		cameraRadius += (Vec2(0.1f, 0.1f) * delta);
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
