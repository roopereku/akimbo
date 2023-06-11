#ifndef AKIMBO_MODULE_HH
#define AKIMBO_MODULE_HH

#include <akimbo/CoreEvent.hh>

namespace Akimbo
{

class Core;
class Module
{
public:
	Module(const Module& rhs) = delete;
	Module& operator=(const Module& rhs) = delete;

	virtual void onUpdate() {};

	friend class Core;

protected:
	Module();
	virtual ~Module() {}

	void emit(CoreEvent event);

	Core& getCore() { return *core; }

private:
	static Core* context;
	Core* core;
};

};

#endif
