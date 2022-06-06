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
		DBG_LOG("Render");
		render.color(1.0f, 1.0f, 1.0f);
		render.clear();
		//render.color(0.0f, 1.0f, 0.0f);
		//render.box(boxAt, Vec2(0.5f, 0.5f), false);
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
