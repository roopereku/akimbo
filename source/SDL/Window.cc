#include <akimbo/SDL/Window.hh>

#include <SDL2/SDL.h>

namespace Akimbo::SDL
{

Window::Window() : window(createWindow()), renderer(window)
{
}

Window::~Window()
{
	if(window)
		SDL_DestroyWindow(window);
}

SDL_Window* Window::createWindow()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* w = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_RESIZABLE);

	return w;
}

void Window::onContentSet()
{
	Vec2i windowSize;
	SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);

	contentResize(windowSize);
}

void Window::onUpdate()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_WINDOWEVENT:
			{
				switch(e.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
					{
						emit(CoreEvent::Close);
						break;
					}

					case SDL_WINDOWEVENT_RESIZED:
					{
						contentResize(Vec2i(e.window.data1, e.window.data2));

						renderer.onResize(e.window.data1, e.window.data2);
						renderContent(renderer);

						break;
					}
				}

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				mouseHeld = true;
				mouseMoved = false;

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				if(!mouseMoved)
					contentMouseClick(Vec2i(e.button.x, e.button.y));

				mouseHeld = false;
				break;
			}

			case SDL_MOUSEMOTION:
			{
				if(mouseHeld)
					contentMouseDrag(Vec2i(e.motion.x, e.motion.y));

				mouseMoved = true;
				break;
			}
		}
	}

	renderContent(renderer);
}

}
