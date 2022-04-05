#include "akimbo/Core.hh"

class Game : public Akimbo::Core
{
public:
	Game() : Akimbo::Core()
	{
	}

	void onRender(Akimbo::Frame& frame) override
	{
		frame.color(255, 255, 255);
		frame.drawLine(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		frame.color(255, 0, 0);
		frame.drawBox(Vec2(0.25f, 0.25f), Vec2(0.25f, 0.25f), false);
		frame.drawBox(Vec2(0.5f, 0.25f), Vec2(0.25f, 0.25f), false);
	}

	void onUpdate(double delta) override
	{
	}
};

int main()
{
	Game g;
	g.start();
}
