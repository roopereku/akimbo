#include "akimbo/Core.hh"

class Test : public Akimbo::Core
{
	void onRender(Akimbo::Render& render) override
	{
		render.color(0.5f, 0.5f, 0.5f);
		render.clear();
	}
};

int main()
{
	Test t;
	t.start();
}
