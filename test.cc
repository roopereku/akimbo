#include "akimbo/Core.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/cardatlas.jpg", 13,5), p(0, 0)
	{
		auto& s = ui.add <Akimbo::UI::Switch> (
			ui.left(75), ui.top(25),
			ui.left(75).then(+0.25f), ui.top(25).then(+0.25f)
		);
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		render.color(0.5f, 0.0f, 0.0f);
		render.box(view.topLeft, view.radius, true);
	}

	void onMouseClick(Vec2 at, int) override
	{
		if(at >= view.topLeft && at <= view.topLeft + view.radius)
		{
		}
	}

private:
	Vec2i p;
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
