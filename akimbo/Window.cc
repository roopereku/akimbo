#include "Window.hh"
#include "Debug.hh"

#include "GL/glew.h"

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

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
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
								SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//	Was the window created
	if(!window)
	{
		fprintf(stderr, "Couldn't create a window: %s\n", SDL_GetError());
		return;
	}

	//	The window size might have changed so let's update it
	SDL_GetWindowSize(window, &size.x, &size.y);
	DBG_LOG("Window created");

	ctx = SDL_GL_CreateContext(window);
	GLenum err = glewInit();

	if(err != GLEW_OK)
	{
		fprintf(stderr, "Couldn't initialize GLEW: %s\n", glewGetErrorString(err));
		return;
	}

	DBG_LOG("GLEW Initialized");
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(window);
}

Window::~Window()
{
	if(window)
	{
		SDL_GL_DeleteContext(ctx);
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

Vec2i Window::swapSize(Vec2i newSize)
{
	Vec2i oldSize = size;
	size = newSize;
	return oldSize;
}

Vec2 Window::toWorldPosition(Vec2i real)
{
	/*	Because (0.0, 0.0) is always the center, we can subtract the real mouse
	 *	position by half of the window size and then divide it with the same value
	 *
	 *	For an example if the window size is (800, 800) and mouse position is (400, 400)
	 *	mouseReal = (400 - 400, 400 - 400) = (0, 0)
	 *	mouseReal / (400, 400) = (0, 0)
	 *
	 *	Or if the window size is (800, 800) and mouse position is (800, 800)
	 *	mouseReal = (800 - 400, 800 - 400) = (400, 400)
	 *	mouseReal / (400, 400) = (1, 1)
	 */
	real -= (size / 2);
	Vec2 world = (Vec2(real) / (Vec2(size) / 2.0f));

	world.y = -world.y;
	DBG_LOG("mouse at (%.2f %.2f)", world.x, world.y);

	return world;
}

}
