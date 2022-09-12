#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"

class Test : public Akimbo::Core
{
public:
	Test() : font(loadFont("/usr/share/fonts/TTF/Comic.TTF")), texture("resources/atlas.png", 4,4)
	{
		//auto& cont1 = ui.add <Akimbo::UI::Container> (
		//	ui.left(50),
		//	ui.top(50),
		//	ui.right(0.1f),
		//	ui.bottom(0.1f)
		//);

		//cont1.add <Akimbo::UI::Switch> (
		//	cont1.left(50).then(-0.2f),
		//	cont1.top(50).then(-0.2f),
		//	cont1.right(50).then(-0.2f),
		//	cont1.bottom(50).then(-0.2f)
		//);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		render.color(1.0f, 1.0f, 1.0f);
		render.text("1234567", font, render.topLeft, Vec2(1.0f, 0.2f));
		render.text("abcjpmg", font, render.topLeft - Vec2(0.0f, 0.2f), Vec2(1.0f, 0.2f));
		render.text("_", font, render.topLeft - Vec2(0.0f, 0.4f), Vec2(1.0f, 0.2f));

		//render.color(1.0f, 1.0f, 1.0f);
		//render.texture(texture, render.topLeft, Vec2(render.radius.y, render.radius.y) * 2.0f);
	}

private:
	Akimbo::TextureAtlas texture;
	Akimbo::Font& font;
};

int main()
{
	Test t;
	t.start();
}
