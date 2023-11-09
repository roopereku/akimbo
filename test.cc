#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/Root.hh>

class Test : public akimbo::Main
{
public:
	Test()
	{
		auto& window = akimbo::SDL2::Window::add();
		window.createRenderer();

		auto& ui = akimbo::UI::Root::add();
		window.content = ui;
	}

private:
};

int main()
{
	Test test;
	test.run();
}
