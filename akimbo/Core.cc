#include "Core.hh"
#include "Debug.hh"

namespace Akimbo {

Core::Core() :	cameraRadius(2.0f, 2.0f), uiRadius(1.0f, 1.0f),
				window("Akimbo", Vec2(0.5f, 0.5f)), uiRoot(this, uiRadius)
{
}

void Core::start()
{
	bool running = window.valid();
	uint64_t lastTicks = SDL_GetTicks();

	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT: return;

				case SDL_WINDOWEVENT:
				{
					switch(event.window.event)
					{
						/*	If a resize happens, we don't wan't to stretch the image
						 *	but adjust the camera radius so that the image remains the same size */
						case SDL_WINDOWEVENT_RESIZED:
						{
							//	Get the old and new windows sizes
							Vec2i newSize(event.window.data1, event.window.data2);
							Vec2i oldSize = window.swapSize(newSize);

							//	Calculate a relation between the sizes
							Vec2 relation = oldSize.as <float> () / newSize.as <float> ();

							//	If the relation isn't just zeroes, adjust the camera and UI radius
							if(relation < Vec2(0.0000f, 0.0000f) || relation > Vec2(0.0000f, 0.0000f))
							{
								cameraRadius = cameraRadius / relation;
								uiRadius = uiRadius / relation;
								uiRoot.adjustPosition(uiRadius);
							}

							break;

						}
					}

					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					//	Get a mouse position that's in (-1, -1) - (+1, +1) range
					Vec2 mousePosition = window.getMousePosition();

					//	Fit the mouse position to the UI space
					Vec2 mouseUI = mousePosition * uiRadius;

					//	Does the click happend inside a widget
					UI::Widget* uiClickAt = uiRoot.isInside(mouseUI);
					if(uiClickAt != &uiRoot)
					{
						//	FIXME pass some sensible value to button
						uiClickAt->onMouseClick(mouseUI, 0);
						break;
					}

					/*	If the click didn't happen inside a widget, fit the mouse
					 *	position to the camera space and pass it to the user */
					Vec2 mouseCamera = mousePosition * cameraRadius + cameraPosition;
					onMouseClick(mouseCamera, 1);
					break;
				}
			}
		}

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
		uiRoot.onUpdate(delta);
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
		uiRoot.onRender(frame);
	}
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

}
