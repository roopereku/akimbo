#ifndef AKIMBO_ENTITY_HH
#define AKIMBO_ENTITY_HH

#include <akimbo/PropertyHost.hh>

namespace akimbo
{

class Core;

class Entity : public PropertyHost
{
public:
	virtual bool isUpdating()
	{
		return false;
	}

protected:
	static Core& getCore();
};

}

#endif
