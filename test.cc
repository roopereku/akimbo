#include "akimbo/Core.hh"
#include "akimbo/ui/Switch.hh"
#include "akimbo/ui/Logger.hh"

class Test : public Akimbo::Core
{
	public:
		Test()
		{
			auto& container1 = ui.add<Akimbo::UI::Container>
				(
					ui.left(50).then(-0.2f),
					ui.top(50).then(-0.3f),
					ui.right(50).then(-0.2f),
					ui.bottom(50).then(-0.2f)
				);

			container1.add<Akimbo::UI::Switch>
				(
				 	container1.left(15),
					container1.top(10),
					container1.right(15),
					container1.bottom(50)
				);

			auto& leg1 = ui.add<Akimbo::UI::Container>
				(
					container1.left(),
					container1.bottom(),
					container1.left(-0.1f),
					container1.bottom(0.1f)
				);

			auto& leg2 = ui.add<Akimbo::UI::Container>
				(
					container1.right(-0.1f),
					container1.bottom(),
					container1.right(),
					container1.bottom(0.1f)
				);

			container1.setBackgroundColor(1.f, 0.f, 0.f);
			leg1.setBackgroundColor(container1);
			leg2.setBackgroundColor(container1);

		}

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
