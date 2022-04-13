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

	void updatePosition(float size);
	Constraint& then(float gap, bool isPercentage = false);

	operator float();

private:
	void updatePosition(float relativePosition, float size);

	Constraint* relative = nullptr;
	std::shared_ptr <Constraint> after;

	bool isPercentage = false;
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
