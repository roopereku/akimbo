#include <akimbo/Entity.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

Core& Entity::getCore()
{
	static thread_local Core core;
	return core;
}

void Entity::executeTasks()
{
	for(size_t i = 0; i < tasks.size(); i++)
	{
		if(tasks[i]->tryFinish())
		{
			tasks.erase(tasks.begin() + i);
			i--;
		}
	}
}

}
