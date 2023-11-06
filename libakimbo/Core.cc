#include <akimbo/Core.hh>

#include <cstdio>

namespace akimbo
{

Core::Core() : isRunning(*this, false)
{
}

void Core::run()
{
	isRunning = true;

	while(isRunning.getValue())
	{
		onUpdate();
	}
}

void Core::onUpdate()
{
	for(auto entity : updatingEntities)
	{
		if(entity->isUpdating())
		{
			entity->onUpdate();
		}
	}
}

}
