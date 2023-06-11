#include <akimbo/Core.hh>
#include <akimbo/SDL/Window.hh>
#include <akimbo/ui/SplitContainer.hh>
#include <akimbo/ui/TabbedContainer.hh>
#include <akimbo/ui/ScrollContainer.hh>

#include <random>

class WhiteButton : public Akimbo::UI::Widget
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
	}

	float r;
	float g;
	float b;
};

class Test : public Akimbo::Core
{
public:
	Test()
	{
		auto& window = add <Akimbo::SDL::Window> ();

		auto& ui = add <Akimbo::UI::HorizontallySplitContainer> ();
		window.setContent(ui);

		auto& cont1 = ui.add <Akimbo::UI::VerticallySplitContainer> ();
		auto& cont2 = ui.add <Akimbo::UI::VerticallySplitContainer> ();

		auto& w1 = cont1.add <WhiteButton> ();
		auto& w2 = cont1.add <TestWidget> ();

		auto& w3 = cont2.add <TestWidget> ();
		auto& w4 = cont2.add <TestWidget> ();
	}

private:
};

int main()
{
	Test t;
	t.run();
}
