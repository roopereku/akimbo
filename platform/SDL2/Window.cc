#include <akimbo/SDL2/Window.hh>
#include <akimbo/SDL2/Renderer2D.hh>
#include <akimbo/Core.hh>

namespace akimbo::SDL2
{

Window& Window::add()
{
	return getCore().addUpdating(new Window());
}

Renderer& Window::createRenderer()
{
	renderer = &SDL2::Renderer2D::add(window);
	return *renderer;
}

Window::Window()
{
	if(SDL_WasInit(SDL_INIT_VIDEO) == 0)
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("Unable to initialize SDL: %s\n", SDL_GetError());
			return;
		}
	}

	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);

	window = SDL_CreateWindow("SDL2 window",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			display.w / 2, display.h / 2, 0);

	if(!window)
	{
		printf("Unable to create SDL window: %s\n", SDL_GetError());
		return;
	}

	printf("Created SDL window\n");
}
	
void Window::onResize()
{
}

void Window::onUpdate()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			getCore().isRunning = false;
		}
	}
}

}
