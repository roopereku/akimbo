#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include "Window.hh"
#include "Texture.hh"

#include <vector>

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
	Texture& loadTexture(const std::string& path);

	Vec2 cameraPosition;
	Vec2 cameraRadius;

private:
	double fpsCapValue = 0;

	std::vector <Texture> textures;
	Window window;
};

}

#endif
