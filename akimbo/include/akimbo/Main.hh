#ifndef AKIMBO_MAIN_HH
#define AKIMBO_MAIN_HH

#include <akimbo/Entity.hh>
#include <akimbo/Core.hh>

namespace akimbo
{

class Main : public Entity
{
public:
	/// Runs Akimbo with the given Main class type.
	template <typename T>
	static void run()
	{
		Main& mainEntity = getCore().add(new T);
		getCore().run();
	}
};

}

#endif
