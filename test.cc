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
	void onRender(akimbo::Renderer2D& renderer) override
	{
		renderer.clear(r, 0.0f, 0.0f);
	}

	void onUpdate() override
	{
		c += 0.01f;
		r = (sin(c) + 1) / 2;

		render();
	}

	float c = 0.0f;
	float r = 0.0f;
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
