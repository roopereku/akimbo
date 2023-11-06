#ifndef AKIMBO_PROPERTY_HH
#define AKIMBO_PROPERTY_HH

namespace akimbo
{

class PropertyHost;

class Property
{
public:
	Property(PropertyHost& host);

	bool operator==(Property& rhs);

protected:
	void triggerChange();

private:
	PropertyHost& host;
};

};

#endif
