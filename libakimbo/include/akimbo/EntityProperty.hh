#ifndef AKIMBO_ENTITY_PROPERTY_HH
#define AKIMBO_ENTITY_PROPERTY_HH

#include <akimbo/Entity.hh>
#include <akimbo/Property.hh>

namespace akimbo
{

template <typename T>
class EntityProperty : public Property
{
public:
	EntityProperty(PropertyHost& host) : Property(host)
	{
	}

	EntityProperty(PropertyHost& host, T& initialValue)
		: Property(host), entity(initialValue.shared_from_this)
	{
	}

	EntityProperty& operator=(T& rhs)
	{
		entity = rhs.shared_from_this();
		triggerChange();

		return *this;
	}

private:
	std::shared_ptr <Entity> entity;
};

}

#endif
