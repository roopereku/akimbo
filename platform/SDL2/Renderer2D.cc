#include <akimbo/SDL2/Renderer2D.hh>
#include <akimbo/Core.hh>

namespace akimbo::SDL2
{

Renderer2D::Renderer2D(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer)
	{
		SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
	}
}

Renderer2D& Renderer2D::add(SDL_Window* window)
{
	return getCore().addUpdating(new Renderer2D(window));
}

void Renderer2D::onUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

}
