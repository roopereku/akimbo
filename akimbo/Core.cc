#include <akimbo/Core.hh>

namespace akimbo
{

Core::Core() : isRunning(*this, false)
{
}

double Core::getDeltaTime()
{
	return deltaTime.count();
}

void Core::run()
{
	isRunning = true;
	auto start = std::chrono::high_resolution_clock::now();

	while(isRunning.getValue())
	{
		auto now = std::chrono::high_resolution_clock::now();
		deltaTime = now - start;
		start = now;

		for(auto entity : entities)
		{
			entity->executeTasks();
		}
	}
}

}
