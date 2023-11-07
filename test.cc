#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Main.hh>

#include <akimbo/SDL2/Window.hh>

class TestContent : public akimbo::WindowContent
{
public:
	static TestContent& add()
	{
		return getCore().addUpdating(new TestContent);
	}

private:
	TestContent()
	{
	}
};

class Test : public akimbo::Main
{
public:
	Test()
	{
		auto& window = akimbo::SDL2::Window::add();
		window.createRenderer();

		auto& content = TestContent::add();
		window.content = content;
	}

private:
};

int main()
{
	Test test;
	test.run();
}
