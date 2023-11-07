#include <akimbo/SDL2/Renderer2D.hh>
#include <akimbo/SDL2/Window.hh>
#include <akimbo/Core.hh>

namespace akimbo::SDL2
{

Renderer2D::Renderer2D(SDL2::Window& target) : akimbo::Renderer2D(target)
{
	renderer = SDL_CreateRenderer(target.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!renderer)
	{
		SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
	}
}

Renderer2D& Renderer2D::add(SDL2::Window& target)
{
	return getCore().addUpdating(new Renderer2D(target));
}

void Renderer2D::display()
{
	SDL_RenderPresent(renderer);
}

void Renderer2D::color(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, a * 255);
}

void Renderer2D::clear(float r, float g, float b, float a)
{
	color(r, g, b, a);
	SDL_RenderClear(renderer);
}

void Renderer2D::clear()
{
	SDL_RenderClear(renderer);
}

}
