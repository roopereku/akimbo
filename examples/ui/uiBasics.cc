#include "../../akimbo/Core.hh"

class Basics : public Akimbo::Core
{
public:
	Basics()
	{
		/*	Every widget lives inside an instance of
		 *	Akimbo::UI::Container. You don't have to create
		 *	one because akimbo provides "ui". */

		/*	Let's add another container inside of "ui" by
		 *	using the add() function */
		auto& container1 = ui.add <Akimbo::UI::Container> (

			//	The left edge sticks to the left edge of "ui"
			ui.left(0.0f, false),

			//	The top edge will stick to the top edge of "ui"
			ui.top(0.0f, false),

			/*	The right edge will be at the middle of "ui". This is
			 *	because "isPercentage" is passed "true" which means that
			 *	0.5f is treated as a percentage. This percentage corresponds
			 *	to a portion of the size of "ui" and that portion will
			 *	be added to whatever ui.left(0.0f, false) is */
			ui.left(0.5f, true),

			//	The bottom edge will stick to the bottom edge of "ui"
			ui.bottom(0.0f, false)

		);

		//	Let's give "container1" a blue background to make it stand out
		container1.setBackgroundColor(0, 0, 255);

		/*	Let's add another container but this time inside "container1"
		 *	Let's also place it at the very center and make it so that
		 *	the size doesn't change. To accomplish we need to use then()
		 *
		 *	What Constraint::then() does it that it applies another operation
		 *	to a constraint, so if you write ui.left(0.5f, true), that
		 *	constraint will be at the center of ui horizontally, but if
		 *	you call ui.left(0.5f, true).then(-0.25f, true),
		 *	the constraint will be only at 25% of "ui".
		 *
		 *	This could be chained with another then() which would look like
		 *	ui.left(0.5f, true).then(-0.25f, true).then(0.5f, true) which
		 *	would make the constraint's final position be at 75% of ui */
		auto& container2 = container1.add <Akimbo::UI::Container> (

			/*	In short terms every constraint is initially at the
			 *	middle of "container1", but they will be shifted
			 *	appropriately so that they're different */
			container1.left(0.5f, true).then(-0.2f, false),
			container1.top(0.5f, true).then(-0.2f, false),
			container1.left(0.5f, true).then(+0.2f, false),
			container1.top(0.5f, true).then(+0.2f, false)

		);

		//	Let's give "container2" a green background to make it stand out
		container2.setBackgroundColor(0, 255, 0);

		/*	Now we have 2 containers that will always appear as
		 *	described even if the user resizes the window. You can
		 *	more widgets inside of these containers by calling add()
		 *	and passing the appropriate constraints.
		 *
		 *	Some widgets have additional parameters which is why you
		 *	should check other examples in examples/ui */
	}

private:
};
