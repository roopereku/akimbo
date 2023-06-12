#include <akimbo/Core.hh>

namespace Akimbo
{

Core::Core()
{
}

void Core::run()
{
	while(running)
	{
		for(auto it : modules)
			it->onUpdate();
	}
}

void Core::handleEvent(CoreEvent event)
{
	switch(event)
	{
		case CoreEvent::Close: running = false; break;
	}
}

}
