#ifndef AKIMBO_UI_CONSTRAINT_HH
#define AKIMBO_UI_CONSTRAINT_HH

#include <memory>

namespace Akimbo::UI {

class Constraint
{
public:
	Constraint(Constraint& relative, float gap, bool isPercentage);
	Constraint(float gap, bool isPercentage);
	Constraint();

	//	then() overloads for units and percents
	Constraint& then(float units);
	Constraint& then(int percents);

	void updatePosition(float size);

	operator float();

	friend class Widget;
	friend class Container;

protected:
	/*	Helper functions that are used for corrections when
	 *	someone uses adds a new widget but doesn't use constraints
	 *	from the container this new widget is being added to */
	bool isRelative(Constraint& constraint);
	void negateGap(bool useRelative);

private:
	Constraint& then(float gap, bool isPercentage);
	void updatePosition(float relativePosition, float size);

	Constraint* relative = nullptr;
	std::shared_ptr <Constraint> after;

	bool isPercentage = false;
	bool useRelative = false;
	bool first = true;

	float position = 0.0f;
	float gap = 0.0f;
};

struct EdgeConstraints
{
	Constraint left;
	Constraint top;
	Constraint right;
	Constraint bottom;
};

}

#endif
