#ifndef AKIMBO_WINDOW_HH
#define AKIMBO_WINDOW_HH

#include "Vector2.hh"

#include <SDL2/SDL.h>

#include <string>

namespace Akimbo {
class Window
{
public:
	Window(const std::string& title, Vec2 sizeMultiplier);
	~Window();

	bool valid() { return window != NULL; }
	void swapBuffer();

	//	Helper which sets a new window size and returns the old one.
	Vec2i swapSize(Vec2i newSize);

	//	Returns some real position converted to a value that's in (-1, -1) - (+1, +1) range
	Vec2 toWorldPosition(Vec2i real);

private:
	SDL_Window* window;
	SDL_GLContext ctx;
	Vec2i size;
};

}

#endif
