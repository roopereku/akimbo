#include "Window.hh"
#include "Debug.hh"

namespace Akimbo {

Window::Window(const std::string& title, Vec2 sizeMultiplier)
{
	//	Don't try to initialize SDL if it's already initialized
	if(!(SDL_WasInit(SDL_INIT_VIDEO) & SDL_INIT_VIDEO))
	{
		DBG_LOG("Trying to initialize SDL");

		//	Is SDL succesfully initialized
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
			return;
		}

		DBG_LOG("SDL Initialized");
	}

	//	TODO support other display indices
	//	How large is the monitor
	SDL_DisplayMode display;
	if(SDL_GetCurrentDisplayMode(0, &display))
	{
		fprintf(stderr, "Couldn't get display info: %s\n", SDL_GetError());
		return;
	}

	DBG_LOG("Display size %dx%d", display.w, display.h);

	//	Attempt to create a window
	window = SDL_CreateWindow(	title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								display.w * sizeMultiplier.x, display.h * sizeMultiplier.y,
								SDL_WINDOW_RESIZABLE);

	//	Was the window created
	if(!window)
	{
		fprintf(stderr, "Couldn't create a window: %s\n", SDL_GetError());
		return;
	}

	//	Attempt to create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//	Was the window created
	if(!renderer)
	{
		fprintf(stderr, "Couldn't create a renderer: %s\n", SDL_GetError());
		return;
	}

	//	The window size might have changed so let's update it
	SDL_GetWindowSize(window, &size.x, &size.y);
	DBG_LOG("Window created");
}

Window::~Window()
{
	if(renderer) SDL_DestroyRenderer(renderer);
	if(window) SDL_DestroyWindow(window);

	SDL_Quit();
}

Frame Window::renderFrame(Vec2& cameraPosition, Vec2& cameraRadius)
{
	return Frame(window, cameraPosition, cameraRadius);
}

Vec2i Window::swapSize(Vec2i newSize)
{
	DBG_LOG("Window now has size %d %d", newSize.x, newSize.y);
	Vec2i oldSize = size;
	size = newSize;
	return oldSize;
}

}
