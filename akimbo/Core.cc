#include <akimbo/Core.hh>

namespace akimbo
{

Core::Core() : isRunning(*this, false)
{
}

void Core::addTask(std::shared_ptr <Task>&& task)
{
	tasks.emplace_back(std::move(task));
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

		for(size_t i = 0; i < tasks.size(); i++)
		{
			if(tasks[i]->tryFinish(getCore()))
			{
				tasks.erase(tasks.begin() + i);
				i--;
			}
		}
	}
}

}
