#include <akimbo/SDL/FontDetail.hh>
#include <akimbo/Vector2.hh>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_log.h>

namespace Akimbo::SDL
{

FontDetail::FontDetail(SDL_Renderer* renderer, std::string_view path)
{
	static bool ttfInitialized = false;
	if(!ttfInitialized)
	{
		TTF_Init();
		ttfInitialized = true;
	}

	char ascii[96];
	for(size_t i = 32; i < 127; i++)
		ascii[i - 32] = i;

	TTF_Font* font = TTF_OpenFont(path.data(), 48);
	if(!font)
	{
		SDL_Log("Couldn't open font '%s': %s", path.data(), TTF_GetError());
		return;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, ascii, { 255, 255, 255, 255 });

	if(!surface)
	{
		SDL_Log("Couldn't create surface for '%s': %s", path.data(), TTF_GetError());
		return;
	}

	int offset = 0;
	atlasSize = Vec2i(surface->w, surface->h);

	for(auto c : ascii)
	{
		Vec2i min;
		Vec2i max;
		int advance;

		TTF_GlyphMetrics(font, c, &min.x, &max.x, &min.y, &max.y, &advance);
		//SDL_Log("'%c' min (%d %d) max (%d %d) advance %d", c, min.x, min.y, max.x, max.y, advance);

		glyphs[c] = { offset, advance };
		offset += advance;
	}

	atlas = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

}
