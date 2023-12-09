#include <akimbo/task/Task.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

double Task::getDeltaTime(Core& context)
{
	return context.getDeltaTime();
}


}
