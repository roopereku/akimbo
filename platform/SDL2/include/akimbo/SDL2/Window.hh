#ifndef AKIMBO_SDL2_WINDOW_HH
#define AKIMBO_SDL2_WINDOW_HH

#include <akimbo/Window.hh>

#include <SDL2/SDL.h>

namespace akimbo::SDL2
{

class Window : public akimbo::Window
{
public:
	static Window& add();

private:
	Window();

	void onResize() override;
	void onUpdate() override;

	SDL_Window* window = nullptr;
};

}

#endif
