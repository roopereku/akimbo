#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"
#include "akimbo/ui/Label.hh"
#include "akimbo/ui/Button.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/atlas.png", 4,4)
	{
		auto& b = ui.add <Akimbo::UI::Logger> (
			ui.left(10), ui.top(10),
			ui.right(10), ui.bottom(10)
		);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		Vec2 pos = render.center;
		Vec2 size = render.radius * Vec2(0.5, 0.25);

		render.color(0.5f, 0.0f, 0.0f);
		render.fitText("123456\ntest\n456j\nm__213890j", getDefaultFont(), pos, size);
	}

private:
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
