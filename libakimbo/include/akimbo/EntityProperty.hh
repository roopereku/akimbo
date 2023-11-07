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
		: Property(host), entity(initialValue.shared_from_this())
	{
	}

	operator bool()
	{
		return static_cast <bool> (entity);
	}

	EntityProperty& operator=(T& rhs)
	{
		entity = rhs.shared_from_this();
		triggerChange();

		return *this;
	}

	T& getValue()
	{
		// TODO: Assert entity validity.
		return static_cast <T&> (*entity);
	}

private:
	std::shared_ptr <Entity> entity;
};

}

#endif
