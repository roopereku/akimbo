#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include "Font.hh"
#include "Window.hh"
#include "Texture.hh"
#include "ui/Container.hh"

#include <vector>

namespace Akimbo {
class Core
{
public:
	Core();
	void start();

private:
	Vec2 cameraRadius;
	Vec2 uiRadius;

	double fpsCapValue = 0;
	Window window;

	std::vector <Texture> textures;
	std::vector <Font> fonts;

protected:
	virtual void onRender(Frame&) {};
	virtual void onUpdate(double) {};
	virtual void onMouseClick(Vec2, int) {};

	void setFpsCap(unsigned cap);
	Font& loadFont(const std::string& path);
	Texture& loadTexture(const std::string& path);

	Vec2 cameraPosition;
	void zoomCamera(float zoom);

	UI::Container uiRoot;
};

}

#endif
