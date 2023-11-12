#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/SplitLayout.hh>

class TestWidget : public akimbo::UI::Widget
{
public:
	static TestWidget& add()
	{
		return getCore().addUpdating(new TestWidget);
	}

	void onRender(akimbo::Renderer2D& render) override
	{
		render.clear(1.0f, 1.0f, 1.0f);
	}

	void onUpdate() override
	{
		render();
	}
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

		auto& testWidget = ui.child(TestWidget::add());
	}

private:
};

int main()
{
	Test test;
	test.run();
}
