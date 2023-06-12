#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include <akimbo/CoreEvent.hh>
#include <akimbo/Module.hh>

#include <memory>
#include <list>

namespace Akimbo
{

class Core
{
public:
	Core();

	template <typename T, typename... Args>
	T& add(Args&&... args)
	{
		Module::context = this;
		modules.emplace_back(std::make_shared <T> (std::forward <Args> (args)...));
		return static_cast <T&> (*modules.back());
	}

	void run();
	void handleEvent(CoreEvent event);

private:
	bool running = true;
	std::list <std::shared_ptr <Module>> modules;
};

}

#endif
