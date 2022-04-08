#ifndef AKIMBO_UI_CONSTRAINT_HH
#define AKIMBO_UI_CONSTRAINT_HH

namespace Akimbo::UI {

class Constraint
{
public:
	Constraint(Constraint& relative, float gap, bool isPercentage);
	Constraint(float gap, bool isPercentage);
	Constraint();

	void updatePosition(float size);
	operator float();

private:
	Constraint* relative = nullptr;
	bool isPercentage = false;
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
