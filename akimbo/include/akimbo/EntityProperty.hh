#ifndef AKIMBO_ENTITY_PROPERTY_HH
#define AKIMBO_ENTITY_PROPERTY_HH

#include <akimbo/Entity.hh>
#include <akimbo/Property.hh>

#include <cassert>

namespace akimbo
{

template <typename T>
class EntityProperty : public Property
{
public:
	EntityProperty(Entity& host) : Property(host)
	{
	}

	EntityProperty(Entity& host, T& initialValue)
		: Property(host), entity(std::static_pointer_cast <T> (initialValue.shared_from_this()))
	{
	}

	EntityProperty(Entity& host, EntityProperty <T>& rhs)
		: Property(host), entity(rhs.entity)
	{
	}

	operator bool()
	{
		return static_cast <bool> (!entity.expired());
	}

	EntityProperty& operator=(T& rhs)
	{
		entity = std::static_pointer_cast <T> (rhs.shared_from_this());
		triggerChange();

		return *this;
	}

	std::shared_ptr <T> getValue()
	{
		assert(!entity.expired());
		return entity.lock();
	}

	std::shared_ptr <T> operator->()
	{
		return getValue();
	}

private:
	std::weak_ptr <T> entity;
};

}

#endif
