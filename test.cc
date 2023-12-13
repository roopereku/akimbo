#include <akimbo/Core.hh>
#include <akimbo/ValueProperty.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Main.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/ui/SplitLayout.hh>
#include <akimbo/ui/ScrollLayout.hh>
#include <akimbo/ui/TabLayout.hh>
#include <akimbo/ui/Toggle.hh>

#include <random>
#include <thread>
#include <functional>

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

		if(at.x > 10 && at.x < 100 && at.y > 10 && at.y < 100)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		else
		{
			addTransitionTask([this](float progress)
			{
				r = progress;
				render();
			}, 3);
		}
	}

	void onDrag(Vec2i at) override
	{
		printf("Drag %d %d\n", at.x, at.y);
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

class Button : public akimbo::UI::Widget
{
public:
	static Button& add(std::function <void()>&& callback)
	{
		return getCore().add(new Button(std::move(callback)));
	}

	void onRender(akimbo::Renderer2D& render) override
	{
		render.clear(0.1, 0.2, 0.3);

		render.color(0.5, 0.5, 0.5);
		render.box(25, 25, size().x - 50, size().y - 50);
	}

	void onClick(Vec2i at) override
	{
		if(at.x >= 25 && at.x <= size().x - 25 && at.y >= 25 && at.y <= size().y - 25)
		{
			if(callback)
			{
				callback();
			}
		}
	}

private:
	Button(std::function <void()>&& callback) : callback(std::move(callback))
	{
	}

	std::function <void()> callback;
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

		auto& container = ui.child(akimbo::UI::SplitLayout::addVertical());

		auto& tabs = container.child(akimbo::UI::TabLayout::addScrolling());
		auto& buttons = container.child(akimbo::UI::SplitLayout::addHorizontal());

		auto& previousButton = buttons.child(Button::add([&tabs]()
		{
			tabs.previous();
		}));

		auto& addButton = buttons.child(Button::add([&tabs]()
		{
			printf("Add tab\n");
			tabs.child(TestWidget::add());
		}));

		auto& nextButton = buttons.child(Button::add([&tabs]()
		{
			tabs.next();
		}));

		tabs.child(TestWidget::add());
	}
};

int main()
{
	akimbo::Main::run <Test> ();
}
