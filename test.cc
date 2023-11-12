#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/SplitLayout.hh>

class TestWidget : public akimbo::UI::Widget
{
public:
	static TestWidget& add(float m)
	{
		return getCore().addUpdating(new TestWidget(m));
	}

	void onRender(akimbo::Renderer2D& render) override
	{
		render.clear(1.0f * m, 1.0f, 1.0f);

		render.color(0.0f, 0.5f, 0.0f);
		render.box(10, 10, 100, 100);
	}

	void onClick(Vec2i at) override
	{
		printf("nii %.2f\n", m);
	}

	void onUpdate() override
	{
		render();
	}

private:
	TestWidget(float m) : m(m)
	{
	}

	float m;
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

		auto& test = ui.child(TestWidget::add(0.5));
		auto& test2 = ui.child(TestWidget::add(0.4));
	}

private:
};

int main()
{
	Test test;
	test.run();
}
