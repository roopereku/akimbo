#ifndef AKIMBO_SDL_TEXTURE_DETAIL_HH
#define AKIMBO_SDL_TEXTURE_DETAIL_HH

#include <akimbo/Texture.hh>
#include <SDL2/SDL_render.h>

#include <string_view>

namespace Akimbo::SDL
{

class TextureDetail : public Akimbo::TextureDetail
{
public:
	TextureDetail(SDL_Renderer* renderer, std::string_view path);
	SDL_Texture* texture;
};

}

#endif
