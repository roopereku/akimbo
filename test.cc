#include "akimbo/Core.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/atlas.png", 4,4), p(0, 0)
	{
		auto& tab = ui.add<Akimbo::UI::TabbedContainer>(
				ui.left(50).then(0.05f), ui.top(10), ui.right(10), ui.bottom(10)
		);

		auto& console = ui.add <Akimbo::UI::Console> (
			ui.left(10), ui.top(10), tab.left(0.1f), ui.bottom(10)
		);

		console.command("add") = [&tab, &console](const std::string& value)
		{
			auto& t = tab.tab(value);

			t.add <Akimbo::UI::Switch> (
				t.left(50).then(-0.25f),
				t.top(50).then(-0.25f),
				t.right(50).then(-0.25f),
				t.bottom(50).then(-0.25f)
			);

			console.log.addMessage("Added tab " + value, Vec3(0.0f, 1.0f, 0.0f));
		};
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}

private:
	Vec2i p;
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
