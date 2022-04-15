#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include "Vector2.hh"
#include "Frame.hh"

#include <SDL2/SDL.h>

#include <string>

namespace Akimbo {
class Window
{
public:
	Window(const std::string& title, Vec2 sizeMultiplier);
	~Window();

	//	Returns a new frame that the user can render something on
	Frame renderFrame(Vec2& cameraPosition, Vec2& cameraRadius);
	bool valid() { return window && renderer; }

	//	Helper which sets a new window size and returns the old one.
	Vec2i swapSize(Vec2i newSize);

	//	Returns some real position converted to a value that's in (-1, -1) - (+1, +1) range
	Vec2 toWorldPosition(Vec2i real);

	/*	Because SDL requires SDL_Renderer to create textures, let's
	 *	expose renderer for the texture & font class which takes
	 *	a Window in it's constructor */
	friend class Texture;
	friend class Font;

private:
	SDL_Window* window;
	Vec2i size;

protected:
	SDL_Renderer* renderer;
};

}

#endif
