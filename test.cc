#include "akimbo/Core.hh"
#include "akimbo/Debug.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Widget.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/cardatlas.jpg", 13,5)
	{
		auto& t = ui.add <Akimbo::UI::TabbedContainer> (
			ui.left(), ui.top(),
			ui.left(75), ui.bottom()
		);

		t.tab("1");
		t.tab("2");

		auto& s = ui.add <Akimbo::UI::Switch> (
			t.right(), t.top(),
			ui.right(), t.bottom()
		);

		s.onSwitch = [&t](bool on)
		{
			if(on) t.setTitleTransparency(0.3f);
			else t.setTitleTransparency(0.6f);
		};
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}

	void onMouseClick(Vec2 at, int) override
	{
		if(at >= view.topLeft && at <= view.topLeft + view.radius)
		{
		}
	}

private:
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
