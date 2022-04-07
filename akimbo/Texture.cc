#include "Texture.hh"
#include "Window.hh"
#include "Debug.hh"

#include <SDL2/SDL_image.h>

#include <cstdio>

namespace Akimbo {

static unsigned textures = 0;

Texture::Texture(const std::string& path, Window* window)
{
	//	If no textures have been created, initialize SDL_Image
	if(textures == 0)
	{
		DBG_LOG("Initializing SDL_Image");

		int flags = IMG_INIT_PNG | IMG_INIT_JPG;
		if(!(IMG_Init(flags) & flags))
		{
			fprintf(stderr, "Couldn't init SDL_image: %s\n", IMG_GetError());
			return;
		}
	}

	DBG_LOG("Loading image '%s'", path.c_str());

	//	Try to load the image
	SDL_Surface* s = IMG_Load(path.c_str());
	if(!s)
	{
		fprintf(stderr, "Couldn't load image '%s': %s\n", path.c_str(), IMG_GetError());
		return;
	}

	//	Try to convert said image to SDL_Texture
	texture = SDL_CreateTextureFromSurface(window->renderer, s);
	if(!texture)
	{
		fprintf(stderr, "Couldn't create texture '%s': %s\n", path.c_str(), SDL_GetError());
		return;
	}

	textures++;
}

Texture::~Texture()
{
	//	If this texture was the last one, quit SDL_Image
	if(texture && --textures == 0)
		IMG_Quit();
}

Texture::Texture(Texture&& rhs) : texture(rhs.texture)
{
	rhs.texture = NULL;
}

}
