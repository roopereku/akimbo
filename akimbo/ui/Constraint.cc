#include "Constraint.hh"
#include "../Debug.hh"

#include <cmath>

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

Constraint& Constraint::then(float units)
{
	return then(units, false);
}

Constraint& Constraint::then(int percents)
{
	return then(static_cast <float> (percents) / 100.0f, true);
}

Constraint& Constraint::then(float gap, bool isPercentage)
{
	/*	Because the first constraint could be a temporary, we need to return
	 *	that. The first constraint always has first set to true */
	Constraint* first = this;
	while(!first->first)
		first = first->relative;

	/*	If this constraint already has a continuation,
	 *	try calling then() on said continuation */
	if(after) return after->then(gap, isPercentage);

	//	If the gap of "first" is negative, negate this one too
	if(std::signbit(first->gap) != 0)
		gap = -gap;

	after = std::make_shared <Constraint> (*this, gap, isPercentage);
	after->first = false;
	
	return *first;
}

bool Constraint::isRelative(Constraint& constraint)
{
	/*	Is the given constraint received from a
	 *	container that this constraint belongs to */
	return relative == constraint.relative->relative;
}

void Constraint::negateGap(bool useRelative)
{
	this->useRelative = useRelative;

	//	Recursively negate this constraint
	gap = -gap;
	if(after) after->negateGap(useRelative);
}

void Constraint::updatePosition(float size)
{
	/*	Because frames imitate a standalone window, the coordinates always
	 *	look something like -1.0, +1.0 - +1.0 - -1.0. If the constraint moves
	 *	to the right, start at -size. If the constraint moves to
	 *	the left, start at + size.
	 *
	 *	There are cases where a widget is being added inside a container but
	 *	the user doesn't use constraints from that container. The positions
	 *	will be screwed up if the relative position isn't used, so let's
	 *	use that instead if useRelative is set to true	*/
	float relativePosition = useRelative ? relative->position : (std::signbit(gap) ? size : -size);
	updatePosition(relativePosition, size);
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
