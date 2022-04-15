#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include "Font.hh"
#include "Window.hh"
#include "Texture.hh"
#include "EventHandler.hh"
#include "ui/Container.hh"

#include <vector>

namespace Akimbo {
class Core
{
public:
	Core();

	//	Starts the main loop
	void start();

private:
	Vec2 cameraRadius;
	Vec2 uiRadius;

	double fpsCapValue = 0;
	Window window;

	std::vector <Texture> textures;
	std::vector <Font> fonts;

	EventHandler events;

protected:
	//	Functions called on each frame
	virtual void onRender(Frame&) {};
	virtual void onUpdate(double) {};

	//	Function that's called when the user clicks on non-UI
	virtual void onMouseClick(Vec2, int) {};

	//	Function that can adjust the FPS cap
	void setFpsCap(unsigned cap);

	Font& loadFont(const std::string& path);
	Texture& loadTexture(const std::string& path);

	//	Where is the camera?
	Vec2 cameraPosition;

	/*	Function that can zoom the camera. For an example zoomCamera(2.0f)
	 *	doubles the camera zoom and zoomCamera(0.5f) halve it */
	void zoomCamera(float zoom);

	//	Root UI container
	UI::Container ui;
};

}

#endif
