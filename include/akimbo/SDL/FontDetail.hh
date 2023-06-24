#ifndef AKIMBO_SDL_FONT_DETAIL_HH
#define AKIMBO_SDL_FONT_DETAIL_HH

#include <akimbo/Font.hh>
#include <akimbo/Vector2.hh>
#include <SDL2/SDL_render.h>

#include <string_view>
#include <unordered_map>

namespace Akimbo::SDL
{

class FontDetail : public Akimbo::FontDetail
{
public:
	FontDetail(SDL_Renderer* renderer, std::string_view path);

	Vec2i atlasSize;
	SDL_Texture* atlas;

	struct GlyphData
	{
		int atlasOffset;
		int advance;
	};

	std::unordered_map <char, GlyphData> glyphs;
};

}

#endif
