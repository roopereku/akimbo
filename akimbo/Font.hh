#ifndef AKIMBO_FONT_HH
#define AKIMBO_FONT_HH

#include "Vector2.hh"

#include <SDL2/SDL_render.h>

#include <string>

namespace Akimbo {

class Window;
class Font
{
public:
	/*	It's a bit stupid to take a window in the texture constructor,
	 *	but for SDL it's necessary because window contains SDL_Renderer */
	Font(const std::string& path, Window* window);
	~Font();

	Font(Font&& rhs);
	friend class Frame;

protected:
	SDL_Texture* texture = NULL;
	Vec2i characterSize;
};

}

#endif
