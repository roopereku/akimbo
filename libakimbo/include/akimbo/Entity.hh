#ifndef AKIMBO_ENTITY_HH
#define AKIMBO_ENTITY_HH

#include <akimbo/Property.hh>

#include <memory>

namespace akimbo
{

class Core;

class Entity : public std::enable_shared_from_this <Entity>
{
public:
	Entity()
	{
	}

	Entity& operator=(const Entity& rhs) = delete;
	Entity(const Entity& rhs) = delete;

	virtual bool isUpdating()
	{
		return false;
	}

	// Property needs access to onPropertyChanged().
	friend class Property;

protected:
	virtual void onPropertyChanged(Property& property)
	{
	}

	static Core& getCore();
};

}

#endif
