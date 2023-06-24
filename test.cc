#include <akimbo/Core.hh>
#include <akimbo/SDL/Window.hh>
#include <akimbo/ui/SplitContainer.hh>
#include <akimbo/ui/TabbedContainer.hh>
#include <akimbo/ui/ScrollContainer.hh>
#include <akimbo/ui/Button.hh>

#include <SDL2/SDL_log.h>

class TestWidget : public Akimbo::UI::Widget
{
public:
	void onLoadResources() override
	{
	}

	void onRender(Akimbo::Render2D& render) override
	{
		render.color(0.4, 0.4, 0.4);
		render.clear();

		render.text(Vec2i(10, 10), Vec2i(150, 50), defaultFont, "test");
	}
};

class Test : public Akimbo::Core
{
public:
	Test()
	{
		auto& window = add <Akimbo::SDL::Window> ();
		auto& ui = add <Akimbo::UI::HorizontallySplitContainer> ();
		window.setContent(ui);

		auto& tabs = ui.add <Akimbo::UI::TabbedContainer> ();
		//auto& scroll = ui.add <Akimbo::UI::ScrollContainer> ();

		tabs.add <TestWidget> ();
		tabs.add <TestWidget> ();
		tabs.add <TestWidget> ();
	}

private:
};

int main()
{
	Test t;
	t.run();
}
