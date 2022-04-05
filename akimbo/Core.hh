#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include "Window.hh"

namespace Akimbo {
class Core
{
public:
	Core();
	void start();

protected:
	virtual void onRender(Frame& frame)=0;
	virtual void onUpdate(double delta)=0;

	void setFpsCap(unsigned cap);

	Vec2 cameraPosition;

private:
	double fpsCapValue = 0;
	Window window;
};

}

#endif
