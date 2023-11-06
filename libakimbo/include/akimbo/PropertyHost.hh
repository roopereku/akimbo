#ifndef AKIMBO_PROPERTY_HOST_HH
#define AKIMBO_PROPERTY_HOST_HH

#include <akimbo/Property.hh>

namespace akimbo
{

class PropertyHost
{
public:
	friend class Property;

protected:
	virtual void onPropertyChanged(Property& property)
	{
	}
};

}

#endif
