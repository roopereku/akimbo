#include <akimbo/Module.hh>
#include <akimbo/Core.hh>

namespace Akimbo
{

Core* Module::context = nullptr;

Module::Module() : core(context)
{
}

void Module::emit(CoreEvent event)
{
	core->handleEvent(event);
}

}
