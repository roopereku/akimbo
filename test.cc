#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"

class Test : public Akimbo::Core
{
public:
	Test() : font(loadFont("/usr/share/fonts/TTF/AndaleMo.TTF"))
	{
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		render.color(1.0f, 1.0f, 1.0f);
		render.character('x', font, render.topLeft + Vec2(0.3f, -0.3f), render.radius);
	}

private:
	Akimbo::Font& font;
};

int main()
{
	Test t;
	t.start();
}
