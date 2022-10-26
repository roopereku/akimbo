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
		auto& l = ui.add <Akimbo::UI::Label> (
			ui.left(25), ui.top(25),
			ui.right(25), ui.bottom(25)
		);

		l.setText("moi\n123\n12345\n22");
		l.setAlign(Akimbo::TextAlign::Right);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

	}

	void onMouseClick(Vec2 at, int) override
	{
	}

private:
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
