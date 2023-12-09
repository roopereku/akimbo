#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/SplitLayout.hh>

#include <random>

class TestWidget : public akimbo::UI::Widget
{
public:
	static TestWidget& add()
	{
		return getCore().add(new TestWidget);
	}

	void onRender(akimbo::Renderer2D& render) override
	{
		render.clear(r, g, b);

		render.color(0.0f, 0.5f, 0.0f);
		render.box(10, 10, 100, 100);
	}

	void onClick(Vec2i at) override
	{
		printf("Clicked %.2f %.2f %.2f\n", r, g, b);
	}

private:
	TestWidget()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution <float> dist(0.0f, 1.0f);

		r = dist(gen);
		g = dist(gen);
		b = dist(gen);

		addRepeatingTask([this]()
		{
			render();
		});
	}

	float r;
	float g;
	float b;
};

class Test : public akimbo::Main
{
public:
	Test()
	{
		auto& window = akimbo::SDL2::Window::add();
		window.createRenderer();

		auto& ui = akimbo::UI::SplitLayout::addRoot();
		window.content = ui;

		auto& left = ui.child(akimbo::UI::SplitLayout::addVertical());
		auto& right = ui.child(TestWidget::add());

		auto& l1 = left.child(TestWidget::add());
		auto& l2 = left.child(TestWidget::add());
		auto& l3 = left.child(akimbo::UI::SplitLayout::addHorizontal());

		auto& inner1 = l3.child(TestWidget::add());
		auto& inner2 = l3.child(TestWidget::add());
	}

private:
};

int main()
{
	akimbo::Main::run <Test> ();
}
