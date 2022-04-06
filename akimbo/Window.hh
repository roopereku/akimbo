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

	Frame renderFrame(Vec2 cameraPosition, Vec2 cameraRadius);
	bool valid() { return window && renderer; }
	Vec2i swapSize(Vec2i newSize);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vec2i size;
};

}

#endif
