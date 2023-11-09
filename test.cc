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
	float getSine(float time, float amplitude, int oscillations)
	{
		float angularFreq = 2 * M_PI * oscillations;
		float phase = 0.0f;

		return (amplitude * sin(angularFreq * time + phase) + 1) / 2;
	}

	void drawSineWave(akimbo::Renderer2D& render)
	{
		float prevX = 0.0f;
		float prevY = 0.0f;

		for(float t = 0.0f; t < 1.0f; t += 0.01f)
		{
			float y1 = window.getValue().height.getValue() * getSine(t + c, 1.0f, 2);
			float y2 = window.getValue().height.getValue() * getSine(t + c, 1.0f, 3);
			float y3 = window.getValue().height.getValue() * getSine(t + c, 1.0f, 4);

			float y = (y1 + y2 + y3) / 3;

			float x = window.getValue().width.getValue() * t;

			render.line(prevX, prevY, x, y);

			prevX = x;
			prevY = y;
		}
	}

	void onRender(akimbo::Renderer2D& render) override
	{
		render.clear(0.0f, 0.0f, 0.0f);

		render.color(1.0f, 0.0f, 0.0f);
		drawSineWave(render);
	}

	void onUpdate() override
	{
		c += 0.005f;
		render();
	}

	float c = 0.0f;
};

class Test : public akimbo::Main
{
public:
	Test()
	{
		auto& window = akimbo::SDL2::Window::add();
		window.createRenderer();

		auto& ui = akimbo::UI::Root::add();
		window.content = content;
	}

private:
};

int main()
{
	Test test;
	test.run();
}
