#include "akimbo/akimbo/Core.hh"

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

			/*	All widgets require 4 constraints which are
			 *	Left edge, Top edge, Right edge and Bottom edge.
			 *
			 *	You can access the constraints of other widgets with functions
			 *	called left(), top(), right(), bottom(). All of said functions take 2 arguments:
			 *	- gap (Defaults to 0.0f)
			 *
			 *		Determines how far this constraint should be from the given edge. For an example
			 *		ui.left(0.1f, false) would shift it right 0.1 units from the root container's left edge.
			 *
			 *	- isPercentage (Defaults to false)
			 *
			 *		Should gap be treated as a percentage? If so, gap will represent a portion of
			 *		of the parent container's size. For an example ui.left(0.1f, true) ends up at
			 *		root container's X + 10% of root container's width */

			/*	NOTE
			 *	If you add a widget that has constraints that are relative to the container the widget is
			 *	being added to, gap will always move in the direction of the center of said container.
			 *	If the constraints are NOT relative to the container, gap will always
			 *	move in the opposite direction of the container's center */

			//	The left edge sticks to the left edge of "ui"
			ui.left(),

			//	The top edge will stick to the top edge of "ui"
			ui.top(),

			//	The right edge will be at the middle of "ui"
			ui.right(0.5f, true),

			//	The bottom edge will stick to the bottom edge of "ui"
			ui.bottom()
		);

		//	Let's give "container1" a blue background to make it stand out
		container1.setBackgroundColor(0, 0, 255);

		/*	Let's add another container but this time inside "container1"
		 *	Let's also place it at the very center and make it so that
		 *	the size doesn't change. To accomplish we need to use then().
		 *
		 *	What Constraint::then() does it that it applies another operation
		 *	to a constraint, so if you write ui.left(0.5f, true), that
		 *	constraint will be at the center of ui horizontally, but if
		 *	you call ui.left(0.5f, true).then(-0.25f, true),
		 *	the constraint will only at at 25% of "ui".
		 *
		 *	This could be chained with another then() which would look like
		 *	ui.left(0.5f, true).then(-0.25f, true).then(0.5f, true) which
		 *	would make the constraint's final position be
		 *	at 75% of the root containers width */
		auto& container2 = container1.add <Akimbo::UI::Container> (

			/*	In short terms every constraint is initially at the
			 *	middle of "container1", but they will be slightly
			 *	moved backwards so that they're not at the same position */
			container1.left(0.5f, true).then(-0.2f),
			container1.top(0.5f, true).then(-0.2f),
			container1.right(0.5f, true).then(-0.2f),
			container1.bottom(0.5f, true).then(-0.2f)

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
};
