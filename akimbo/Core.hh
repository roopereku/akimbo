#ifndef AKIMBO_CORE_HH
#define AKIMBO_CORE_HH

#include "Font.hh"
#include "Frame.hh"
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
	UI::Widget* widgetFocus = nullptr;
	double fpsCapValue = 0;
	Window window;

	std::vector <Texture> textures;
	std::vector <Font> fonts;

	EventHandler events;
	Frame frame;

protected:
	virtual void onRender(Render& render);
	virtual void onUpdate(double delta);

	//	Function that's called when the user clicks on non-UI
	virtual void onMouseClick(Vec2 at, int button);

	//	Function that's called when the user presses a key when UI isn't focused
	virtual void onKeyPress(char key);
	virtual void onKeyPress(Key key);

	//	Function that can adjust the FPS cap
	void setFpsCap(unsigned cap);

	void render();

	Font& loadFont(const std::string& path);
	Texture& loadTexture(const std::string& path);

	//	Focus on some widget
	void setWidgetFocus(UI::Widget& widget);

	//	Root UI container
	UI::Container ui;
};

}

#endif
