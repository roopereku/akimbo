#ifndef AKIMBO_RENDDERER_HH
#define AKIMBO_RENDDERER_HH

#include <akimbo/UpdatingEntity.hh>

namespace akimbo
{

class Renderer : public UpdatingEntity
{
public:

protected:
	virtual void onUpdate() override = 0;
};

}

#endif
