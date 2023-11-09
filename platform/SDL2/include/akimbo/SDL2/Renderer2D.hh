#ifndef AKIMBO_SDL2_RENDERER2D_HH
#define AKIMBO_SDL2_RENDERER2D_HH

#include <akimbo/Renderer2D.hh>

#include <SDL2/SDL.h>

namespace akimbo::SDL2
{

class Window;

class Renderer2D : public akimbo::Renderer2D
{
public:
	static Renderer2D& add(SDL2::Window& target);

	void color(float r, float g, float b, float a = 1.0f) override;
	void display() override;

	void clear(float r, float g, float b, float a = 1.0f) override;
	void clear() override;

	void box(int x, int y, int w, int h) override;
	void line(int x1, int y1, int x2, int y2) override;

private:
	Renderer2D(SDL2::Window& target);

	SDL_Renderer* renderer;
};

}

#endif
