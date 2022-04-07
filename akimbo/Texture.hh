#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include <SDL2/SDL_render.h>

#include <string>

namespace Akimbo {

class Window;
class Texture
{
public:
	/*	It's a bit stupid to take a window in the texture constructor,
	 *	but for SDL it's necessary because window contains SDL_Renderer */
	Texture(const std::string& path, Window* window);
	~Texture();

	Texture(Texture&& rhs);
	friend class Frame;

protected:
	SDL_Texture* texture = NULL;
};

}

#endif
