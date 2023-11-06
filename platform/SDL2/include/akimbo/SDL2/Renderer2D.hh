#ifndef AKIMBO_SDL2_RENDERER2D_HH
#define AKIMBO_SDL2_RENDERER2D_HH

#include <akimbo/Renderer.hh>

#include <SDL2/SDL.h>

namespace akimbo::SDL2
{

class Renderer2D : public akimbo::Renderer
{
public:
	static Renderer2D& add(SDL_Window* window);

private:
	Renderer2D(SDL_Window* window);
	void onUpdate() override;

	SDL_Renderer* renderer;
};

}

#endif
