#include "Frame.hh"
#include "Debug.hh"

namespace Akimbo {

Frame::Frame(SDL_Window* w, Vec2 cameraPosition, float cameraZoom)
	: window(w), cameraPosition(cameraPosition), cameraZoom(cameraZoom)
{
	color(0, 0, 0);
	SDL_RenderClear(SDL_GetRenderer(window));
}

Frame::~Frame()
{
	SDL_RenderPresent(SDL_GetRenderer(window));
}

void Frame::drawBox(Vec2 position, Vec2 size, bool filled)
{
	/*	TODO Support world space range that looks like (-1.0f, -1.0f) - (+1.0f, +1.0f)
	 *	This can be done by subtracting the radius of the world space from the size */

	Vec2i p = convert(position).as <int> ();
	Vec2i s = convert(size).as <int> ();

	SDL_Rect r { p.x, p.y, s.x + 1, s.y + 1 };
	if(filled) SDL_RenderFillRect(SDL_GetRenderer(window), &r);
	else SDL_RenderDrawRect(SDL_GetRenderer(window), &r);
}

void Frame::drawLine(Vec2 from, Vec2 to)
{
	from = convert(from);
	to = convert(to);

	SDL_RenderDrawLine(SDL_GetRenderer(window), from.x, from.y, to.x, to.y);
}

void Frame::drawDot(Vec2 position)
{
	position = convert(position);
	SDL_RenderDrawPoint(SDL_GetRenderer(window), position.x, position.y);
}

void Frame::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(SDL_GetRenderer(window), r, g, b, a);
}

Vec2 Frame::convert(Vec2 position)
{
	int w;
	int h;

	//	Move the point depending on where the camera is
	position -= cameraPosition;

	//	TODO Support world space range that looks like (-1.0f, -1.0f) - (+1.0f, +1.0f)
	/*	Assuming that the input is (0.5f, 0.5f), multiply said input with
	 *	the window size so that the point ends up at the middle of the window */
	SDL_GetWindowSize(window, &w, &h);
	return Vec2(position.x * w, position.y * h);
}


}
