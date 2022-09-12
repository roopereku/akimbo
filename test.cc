#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"

class Test : public Akimbo::Core
{
public:
	Test() : font(loadFont("/usr/share/fonts/TTF/Comic.TTF")), texture("resources/atlas.png", 4,4)
	{
		auto& logger = ui.add <Akimbo::UI::Logger> (
			ui.left(10),
			ui.top(10),
			ui.right(10),
			ui.bottom(10),
			font
		);

		auto& check = ui.add <Akimbo::UI::Switch> (
			logger.left(0.4f),
			logger.top(),
			logger.left(),
			logger.bottom()
		);

		check.onSwitch = [&logger](bool on)
		{
			if(on) logger.setRows(5);
			else logger.setRows(10);
		};
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
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
