#ifndef AKIMBO_UPDATING_ENTITY_HH
#define AKIMBO_UPDATING_ENTITY_HH

#include <akimbo/Entity.hh>

namespace akimbo
{

class Core;

class UpdatingEntity : public Entity
{
public:
	bool isUpdating() final override
	{
		return true;
	}

	friend class Core;

protected:
	virtual void onUpdate() = 0;
};

}

#endif
