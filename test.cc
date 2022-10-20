#include "akimbo/Core.hh"
#include "akimbo/ui/Console.hh"
#include "akimbo/ui/TabbedContainer.hh"
#include "akimbo/ui/Switch.hh"

class Test : public Akimbo::Core
{
public:
	Test() : texture("resources/cardatlas.jpg", 13,5), p(0, 0)
	{
	}

	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();

		Vec2 size(0.5f, 0.5f);

		render.color(1.0f, 1.0f, 1.0f);
		render.texture(texture, render.center, render.radius);
		render.fromAtlas(texture, 0, 1, render.topLeft, size * texture.getAspectRatio());
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
