#include "Core.hh"
#include "Debug.hh"
#include "Mesh.hh"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Akimbo {

Core::Core() : window("Akimbo", Vec2(0.5f, 0.5f)), ui(this, Vec2())
{
	events.onKeyPress = [this](char key)
	{
		//	If a widget is focused, pass the keypress to it
		if(widgetFocus)
			widgetFocus->onKeyPress(key);

		else onKeyPress(key);
	};

	events.onKeyPressOther = [this](Key key)
	{
		//	If a widget is focused, pass the keypress to it
		if(widgetFocus)
			widgetFocus->onKeyPress(key);

		else onKeyPress(key);
	};

	events.onMouseClick = [this](Vec2i realPosition, int button)
	{
		//	Get a mouse position that's in (-1, -1) - (+1, +1) range
		Vec2 mousePosition = window.toWorldPosition(realPosition);

		//	Fit the mouse position to the UI space
		Vec2 mouseUI = mousePosition;

		//	Does the click happen inside a widget
		UI::Widget* uiClickAt = ui.isInside(mouseUI);
		if(uiClickAt != &ui)
		{
			setWidgetFocus(*uiClickAt);
			uiClickAt->onMouseClick(mouseUI, button);
			return;
		}

		//	We're no longer focused on any widgets
		widgetFocus = nullptr;

		/*	If the click didn't happen inside a widget, fit the mouse
		 *	position to the camera space and pass it to the user */
		//Vec2 mouseCamera = mousePosition * cameraRadius + cameraPosition;
		onMouseClick(mousePosition, button);
	};

	events.onWindowResize = [this](Vec2i newSize)
	{
		Vec2i oldSize = window.swapSize(newSize);

		frame.resize(newSize);
		ui.resize(newSize);

		render();
	};
}

void Core::render()
{
	Render r = frame.render();
	onRender(r);
}

void Core::start()
{
	ui.renderSelf();
	render();

	bool running = window.valid();
	uint64_t lastTicks = SDL_GetTicks();

	events.onWindowClose = [&running]()
	{
		running = false;
	};

	while(running)
	{
		//	Handle events
		events.update();

		//	The window might have closed
		if(!running) break;

		//	Calculate a delta time
		uint32_t ticks = SDL_GetTicks();
		double delta = (double)(ticks - lastTicks) / 1000.0f;
		lastTicks = ticks;

		//	Because 0 means no FPS cap, don't sleep if the cap is 0
		if(fpsCapValue > 0)
		{
			SDL_Delay(fpsCapValue * 1000);
			delta = fpsCapValue;
		}

		//	Call updates
		ui.onUpdate(delta);
		//onUpdate(delta);

		frame.draw();
		ui.draw();

		window.swapBuffer();
	}
}

void Core::setWidgetFocus(UI::Widget& widget)
{
	widgetFocus = &widget;
}

void Core::setFpsCap(unsigned cap)
{
	DBG_LOG("Capped FPS to %u", cap);
	fpsCapValue = 1.0 / cap;
}

Texture& Core::loadTexture(const std::string& path)
{
	textures.emplace_back(path);
	return textures.back();
}

Font& Core::loadFont(const std::string& path)
{
	fonts.emplace_back(path);
	return fonts.back();
}

void Core::onRender(Render&) {}
void Core::onUpdate(double) {}
void Core::onMouseClick(Vec2, int) {}
void Core::onKeyPress(char) {}
void Core::onKeyPress(Key) {}

}
