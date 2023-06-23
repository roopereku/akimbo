#include <akimbo/Core.hh>
#include <akimbo/SDL/Window.hh>
#include <akimbo/ui/SplitContainer.hh>
#include <akimbo/ui/TabbedContainer.hh>
#include <akimbo/ui/ScrollContainer.hh>
#include <akimbo/ui/Button.hh>
#include <SDL2/SDL_log.h>

#include <random>

class WhiteButton : public Akimbo::UI::Button
{
public:
	void onRender(Akimbo::Render2D& render) override
	{
		render.color(0.8f, 0.8f, 0.8f);
		render.clear();

		render.color(0.5f, 0.5f, 0.5f);
		render.box(Vec2(0.25f, 0.25f), Vec2(0.5f, 0.5f));
	}
};

class TestWidget : public Akimbo::UI::Widget
{
public:
	TestWidget()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution <float> dist(0.0f, 1.0f);

		r = dist(gen);
		g = dist(gen);
		b = dist(gen);
	}

	void onRender(Akimbo::Render2D& render) override
	{
		render.color(r, g, b);
		render.clear();

		render.color(1, 1, 1);
		render.box(Vec2i(10, 10), Vec2i(100, 100));

		render.texture(Vec2i(150, 150), Vec2i(100, 100), t);
	}

	void onAttached() override
	{
		t = getRenderer().createTexture("cat.png");
	}

	float r;
	float g;
	float b;

	Akimbo::Texture t;
};

class Test : public Akimbo::Core
{
public:
	Test()
	{
		auto& window = add <Akimbo::SDL::Window> ();
		auto& ui = add <Akimbo::UI::HorizontallySplitContainer> ();
		window.setContent(ui);

		auto& left = ui.add <Akimbo::UI::VerticallySplitContainer> ();
		auto& leftTabs = left.add <Akimbo::UI::TabbedContainer> ();

		leftTabs.add <TestWidget> ();

		auto& scrollContainer1 = leftTabs.add <Akimbo::UI::ScrollContainer> ();
		auto& bcd1 = scrollContainer1.add <TestWidget> ();
		auto& bcd2 = scrollContainer1.add <WhiteButton> ();
		auto& bcd3 = scrollContainer1.add <TestWidget> ();

		scrollContainer1.setMaximumSize(bcd1, 150);
		scrollContainer1.setMaximumSize(bcd2, 340);

		bcd2.onClick = [&leftTabs](Akimbo::UI::Button& self)
		{
			SDL_Log("click");
			leftTabs.add <TestWidget> ();
		};

		leftTabs.add <TestWidget> ();

		auto& tabContainer1 = leftTabs.add <Akimbo::UI::HorizontallySplitContainer> ();
		auto& abc1 = tabContainer1.add <TestWidget> ();
		auto& abc2 = tabContainer1.add <TestWidget> ();
	}

private:
};

int main()
{
	Test t;
	t.run();
}
