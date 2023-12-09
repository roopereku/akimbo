#include <akimbo/Core.hh>

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
		for(auto entity : entities)
		{
			entity->executeTasks();
		}
	}
}

}
