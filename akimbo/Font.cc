#include "Window.hh"
#include "Debug.hh"
#include "Font.hh"

#include <SDL2/SDL_ttf.h>

#include <cstdio>

namespace Akimbo {

static unsigned fonts = 0;

Font::Font(const std::string& path, Window* window)
{
	//	If no fonts have been created, initialize SDL_TTF
	if(fonts == 0)
	{
		DBG_LOG("Initializing SDL_TTF");

		if(TTF_Init() < 0)
		{
			fprintf(stderr, "Couldn't init SDL_TTF: %s\n", TTF_GetError());
			return;
		}
	}

	DBG_LOG("Loading font '%s'", path.c_str());

	//	Try to load the font
	TTF_Font* font = TTF_OpenFont(path.c_str(), 24);
	if(!font)
	{
		fprintf(stderr, "Couldn't load font '%s': %s\n", path.c_str(), TTF_GetError());
		return;
	}

	std::string ascii(95, 0);
	for(size_t i = 0; i < ascii.length(); i++)
		ascii[i] = i + 32;

	SDL_Surface* s = TTF_RenderText_Solid(font, ascii.c_str(), { 255, 255, 255, 255 });
	if(!s)
	{
		fprintf(stderr, "Couldn't render font '%s': %s\n", path.c_str(), TTF_GetError());
		return;
	}

	characterSize = Vec2i(s->w / ascii.length(), s->h);

	//	Try to convert said image to SDL_Texture
	texture = SDL_CreateTextureFromSurface(window->renderer, s);
	if(!texture)
	{
		fprintf(stderr, "Couldn't create font '%s': %s\n", path.c_str(), SDL_GetError());
		return;
	}

	fonts++;
}

Font::~Font()
{
	//	If this texture was the last one, quit SDL_Image
	if(texture && --fonts == 0)
		TTF_Quit();
}

Font::Font(Font&& rhs) : texture(rhs.texture)
{
	rhs.texture = NULL;
}

}
