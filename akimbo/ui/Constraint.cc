#include "Constraint.hh"
#include "../Debug.hh"

namespace Akimbo::UI {

Constraint::Constraint(Constraint& relative, float gap, bool isPercentage)
	: relative(&relative), isPercentage(isPercentage), gap(gap)
{
}

Constraint::Constraint(float gap, bool isPercentage)
	: isPercentage(isPercentage), gap(gap)
{
}

Constraint::Constraint()
{
}

Constraint& Constraint::then(float gap, bool isPercentage)
{
	/*	If this constraint already has a continuation,
	 *	try calling then() on said continuation */
	if(after) return after->then(gap, isPercentage);

	after = std::make_shared <Constraint> (*this, gap, isPercentage);
	after->first = false;
	
	/*	Because the first constraint could be a temporary, we need to return
	 *	that. The first constraint always has first set to true */
	Constraint* first = this;
	while(!first->first)
		first = first->relative;

	return *first;
}

void Constraint::updatePosition(float size)
{
	//	If there's no relative position, start at the top left corner
	updatePosition(relative ? relative->position : -size, size);
}

void Constraint::updatePosition(float relativePosition, float size)
{
	position = relativePosition;

	//	Is gap meant to be a percentage
	if(isPercentage) position += (size * 2 * gap);

	//	Gap isn't a percentage
	else position += gap;

	//	Update the constraint called by then()
	if(after)
	{
		after->updatePosition(position, size);

		/*	Assuming that the intermediate positions aren't needed
		 *	at this point, let's make all of them identical to
		 *	the final position so that we don't have to
		 *	find it when it should be used */
		position = after->position;
	}
}

Constraint::operator float()
{
	return position;
}

}
