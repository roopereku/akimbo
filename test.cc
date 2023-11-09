#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/SplitLayout.hh>

class Test : public akimbo::Main
{
public:
	Test()
	{
		auto& window = akimbo::SDL2::Window::add();
		window.createRenderer();

		auto& ui = akimbo::UI::SplitLayout::addRoot();
		window.content = ui;

		auto& split1 = ui.child(akimbo::UI::SplitLayout::addVertical());
	}

private:
};

int main()
{
	Test test;
	test.run();
}
