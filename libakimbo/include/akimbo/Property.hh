#ifndef AKIMBO_PROPERTY_HH
#define AKIMBO_PROPERTY_HH

namespace akimbo
{

class Entity;

class Property
{
public:
	Property(Entity& host);

	bool operator==(Property& rhs);

protected:
	void triggerChange();

private:
	Entity& host;
};

};

#endif
