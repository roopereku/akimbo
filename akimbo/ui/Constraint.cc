#include "Constraint.hh"

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

void Constraint::updatePosition(float size)
{
	//	If there's no relative position, start at the top left corner
	if(relative) position = relative->position;
	else position = -size;

	//	Is gap meant to be a percentage
	if(isPercentage) position += (size * 2 * gap);

	//	Gap isn't a percentage
	else position += gap;
}

Constraint::operator float()
{
	return position;
}

}
