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

}
