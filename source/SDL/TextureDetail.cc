#include <akimbo/SDL/TextureDetail.hh>
#include <SDL2/SDL_image.h>

namespace Akimbo::SDL
{

TextureDetail::TextureDetail(SDL_Renderer* renderer, std::string_view path)
{
	static bool imgInitialized = false;
	if(!imgInitialized)
	{
		IMG_Init(IMG_INIT_PNG);
		imgInitialized = true;
	}

	SDL_Surface* surface = IMG_Load(path.data());

	if(!surface)
	{
		SDL_Log("Couldn't load texture: %s", IMG_GetError());
		return;
	}

	size = Vec2i(surface->w, surface->h);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
}

}
