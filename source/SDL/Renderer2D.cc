#include <akimbo/SDL/Renderer2D.hh>

namespace Akimbo
{

namespace SDL
{

Render2D::Render2D(SDL_Renderer* renderer, Vec2i offset, Vec2i screenSize)
	: renderer(renderer), offset(offset), screenSize(screenSize)
{
}

void Render2D::color(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, a * 255);
}

void Render2D::clear()
{
	box(Vec2(0, 0), Vec2(1, 1));
}

void Render2D::box(Vec2 position, Vec2 size)
{
	SDL_Rect r
	{
		static_cast <int> (offset.x + position.x * screenSize.x),
		static_cast <int> (offset.y + position.y * screenSize.y),
		static_cast <int> (size.x * screenSize.x),
		static_cast <int> (size.y * screenSize.y)
	};

	SDL_RenderFillRect(renderer, &r);
}

void Render2D::target(Vec2 position, Vec2 size, RenderTarget2D& rt)
{
	Vec2i targetOffset(
		offset.x + (position.x * screenSize.x),
		offset.y + (position.y * screenSize.y)
	);

	Vec2i targetSize(
		size.x * screenSize.x,
		size.y * screenSize.y
	);

	SDL_Rect clipRect = { offset.x, offset.y, screenSize.x, screenSize.y };
	SDL_RenderSetClipRect(renderer, &clipRect);

	Render2D render(renderer, targetOffset, targetSize);
	rt.onRender(render);

	SDL_RenderSetClipRect(renderer, &clipRect);
}

Renderer2D::Renderer2D(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer2D::~Renderer2D()
{
	if(renderer)
		SDL_DestroyRenderer(renderer);
}

void Renderer2D::render(RenderTarget& target)
{
	Render2D render(renderer, Vec2i(0, 0), screenSize);
	static_cast <RenderTarget2D&> (target).onRender(render);

	SDL_RenderPresent(renderer);
}

void Renderer2D::onResize(unsigned w, unsigned h)
{
	screenSize.x = w;
	screenSize.y = h;
}

}

}
