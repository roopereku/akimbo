#include "Core.hh"
#include "Debug.hh"

namespace Akimbo {

Core::Core() : cameraRadius(1.0f, 1.0f), window("Akimbo", Vec2(0.5f, 0.5f))
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

							//	If the relation isn't just zeroes, adjust the camera radius
							if(relation < Vec2(0.0000f, 0.0000f) || relation > Vec2(0.0000f, 0.0000f))
								cameraRadius = cameraRadius / relation;
						}
					}

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

		//	Create a new frame that the user can use for drawing
		Frame frame = window.renderFrame(cameraPosition, cameraRadius);

		onUpdate(delta);
		onRender(frame);
	}
}

void Core::setFpsCap(unsigned cap)
{
	DBG_LOG("Capped FPS to %u", cap);
	fpsCapValue = 1.0 / cap;
}

Texture& Core::loadTexture(const std::string& path)
{
	textures.emplace_back(path, &window);
	return textures.back();
}

}
