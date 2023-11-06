#include <akimbo/Entity.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

Core& Entity::getCore()
{
	static thread_local Core core;
	return core;
}

}
