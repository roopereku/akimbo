#ifndef AKIMBO_ENTITY_HH
#define AKIMBO_ENTITY_HH

#include <akimbo/PropertyHost.hh>

namespace akimbo
{

class Core;

class Entity : public PropertyHost
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

protected:
	static Core& getCore();
};

}

#endif
