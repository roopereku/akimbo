#ifndef AKIMBO_SDL_RENDERER2D_HH
#define AKIMBO_SDL_RENDERER2D_HH

#include <akimbo/Renderer2D.hh>
#include <SDL2/SDL_render.h>

#include <vector>

namespace Akimbo::SDL
{

class Render2D : public Akimbo::Render2D
{
public:
	void color(float r, float g, float b, float a = 1.0f) override;
	void clear() override;

	void box(Vec2 position, Vec2 size) override;
	void box(Vec2i position, Vec2i size) override;

	void target(Vec2 position, Vec2 size, RenderTarget2D& rt) override;
	void target(Vec2i position, Vec2i size, RenderTarget2D& rt) override;

	friend class Renderer2D;

private:
	Render2D(SDL_Renderer* renderer, Vec2i offset, Vec2i screenSize);

	SDL_Renderer* renderer;
	Vec2i offset;
	Vec2i screenSize;

	std::vector <SDL_Rect> overlays;
};

class Renderer2D : public Akimbo::Renderer
{
public:
	Renderer2D(SDL_Window* window);
	~Renderer2D();

	void render(RenderTarget& target) override;
	void onResize(unsigned w, unsigned h) override;

private:
	Vec2i screenSize;
	SDL_Renderer* renderer;
};

}

#endif
