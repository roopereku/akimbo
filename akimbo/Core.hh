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

	UI::Widget* widgetFocus = nullptr;
	double fpsCapValue = 0;
	Window window;

	std::vector <Texture> textures;
	std::vector <Font> fonts;

	EventHandler events;

protected:
	//	Functions called on each frame
	virtual void onRender(Frame& frame);
	virtual void onUpdate(double delta);

	//	Function that's called when the user clicks on non-UI
	virtual void onMouseClick(Vec2 at, int button);

	//	Function that's called when the user presses a key when UI isn't focused
	virtual void onKeyPress(char key);
	virtual void onKeyPress(Key key);

	//	Function that can adjust the FPS cap
	void setFpsCap(unsigned cap);

	Font& loadFont(const std::string& path);
	Texture& loadTexture(const std::string& path);

	//	Where is the camera?
	Vec2 cameraPosition;

	/*	Function that can zoom the camera. For an example zoomCamera(2.0f)
	 *	doubles the camera zoom and zoomCamera(0.5f) halve it */
	void zoomCamera(float zoom);

	//	Focus on some widget
	void setWidgetFocus(UI::Widget& widget);

	//	Root UI container
	UI::Container ui;
};

}

#endif
