#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"
#include "akimbo/ui/Label.hh"
#include "akimbo/ui/Button.hh"
#include "akimbo/ui/TextInput.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/atlas.png", 4,4)
	{
		auto& b = ui.add <Akimbo::UI::Logger> (
			ui.left(10), ui.top(10),
			ui.right(10), ui.bottom(50)
		);

		auto& l = ui.add <Akimbo::UI::TextInput> (
			ui.left(50).then(-0.9f), b.bottom(0.1f),
			ui.right(50).then(-0.9f), b.bottom(0.4f)
		);

		b.setRows(10);
		l.onSubmit = [&b](const std::string& text)
		{
			b.addMessage(text);
		};
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}

private:
	Akimbo::TextureAtlas texture;
};

int main()
{
	Test t;
	t.start();
}
