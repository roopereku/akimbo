#ifndef AKIMBO_UPDATING_ENTITY_HH
#define AKIMBO_UPDATING_ENTITY_HH

#include <akimbo/Entity.hh>

#include <memory>

namespace akimbo
{

class Core;

class UpdatingEntity : public Entity, std::enable_shared_from_this <UpdatingEntity>
{
public:
	UpdatingEntity();

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
