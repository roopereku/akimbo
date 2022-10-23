#include "akimbo/Core.hh"
#include "akimbo/Debug.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Widget.hh"

class Overlay : public Akimbo::UI::Widget
{
public:
	void onMouseClick(Vec2, int) override
	{
		DBG_LOG("overlay clicked");
	}
};

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/cardatlas.jpg", 13,5)
	{
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
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
