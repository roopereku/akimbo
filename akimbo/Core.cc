#include "Core.hh"
#include "Debug.hh"

namespace Akimbo {

Core::Core() :	cameraRadius(2.0f, 2.0f), uiRadius(1.0f, 1.0f),
				window("Akimbo", Vec2(0.5f, 0.5f)), ui(this, uiRadius)
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
		Vec2 mouseUI = mousePosition * uiRadius;

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
		Vec2 mouseCamera = mousePosition * cameraRadius + cameraPosition;
		onMouseClick(mouseCamera, button);
	};

	events.onWindowResize = [this](Vec2i newSize)
	{

		/*	If a resize happens, we don't wan't to stretch the image
		 *	but adjust the camera radius so that the image remains the same size */

		//	Request the old size from the window
		Vec2i oldSize = window.swapSize(newSize);

		//	Calculate a relation between the sizes
		Vec2 relation = oldSize.as <float> () / newSize.as <float> ();

		//	If the relation isn't just zeroes, adjust the camera and UI radius
		if(relation < Vec2(0.0000f, 0.0000f) || relation > Vec2(0.0000f, 0.0000f))
		{
			cameraRadius = cameraRadius / relation;
			uiRadius = uiRadius / relation;
			ui.adjustPosition(uiRadius);
		}
	};

}

void Core::start()
{
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
		onUpdate(delta);

		//	Create a new frame that the user can use for drawing
		Vec2 radius = cameraRadius;
		Vec2 position = cameraPosition;
		Frame frame = window.renderFrame(position, radius);

		//	Call user defined rendering
		onRender(frame);

		/*	The UI shouldn't use the camera in any way so let's trick
		 *	the frame and modify the position and radius to fit the UI */
		position = Vec2(0.0f, 0.0f);
		radius = uiRadius;

		//	Render the UI
		ui.onRender(frame);
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

void Core::zoomCamera(float zoom)
{
	cameraRadius = cameraRadius / zoom;
}

Texture& Core::loadTexture(const std::string& path)
{
	textures.emplace_back(path, &window);
	return textures.back();
}

Font& Core::loadFont(const std::string& path)
{
	fonts.emplace_back(path, &window);
	return fonts.back();
}

void Core::onRender(Frame&) {}
void Core::onUpdate(double) {}
void Core::onMouseClick(Vec2, int) {}
void Core::onKeyPress(char) {}
void Core::onKeyPress(Key) {}

}
