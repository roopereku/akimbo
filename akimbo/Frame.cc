#include "Frame.hh"
#include "Debug.hh"

namespace Akimbo {

Frame::Frame(SDL_Window* w, Vec2& cameraPosition, Vec2& cameraRadius)
	: window(w), cameraPosition(cameraPosition), cameraRadius(cameraRadius)
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
	Vec2i p = convert(position).as <int> ();
	Vec2i s = convert(size - cameraRadius).as <int> ();
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

void Frame::drawTexture(Texture& texture, Vec2 position, Vec2 size)
{
	Vec2i p = convert(position).as <int> ();
	Vec2i s = convert(size - cameraRadius).as <int> ();
	SDL_Rect r { p.x, p.y, s.x + 1, s.y + 1 };

	SDL_RenderCopy(SDL_GetRenderer(window), texture.texture, NULL, &r);
}

void Frame::drawCharacter(char chr, Font& font, Vec2 position, Vec2 size)
{
	//	Calculate the position of the character in the font
	int index = chr - 32;
	int x = font.characterSize.x * index;

	Vec2i p = convert(position).as <int> ();
	Vec2i s = convert(size - cameraRadius).as <int> ();

	SDL_Rect r { p.x, p.y, s.x + 1, s.y + 1 };
	SDL_Rect src { x, 0, font.characterSize.x, font.characterSize.y };

	//	Draw the given character from the font texture
	SDL_RenderCopy(SDL_GetRenderer(window), font.texture, &src, &r);
}

void Frame::drawText(const std::string& str, Font& font, Vec2 position, Vec2 size)
{
	size_t longestLine = 0;
	size_t lineLength = 0;
	size_t lines = 1;

	//	First find all the line breaks and the longest line
	for(auto c : str)
	{
		if(c == '\n')
		{
			if(lineLength > longestLine)
				longestLine = lineLength;

			lines++;
			lineLength = 0;
		}

		else lineLength++;
	}

	//	There might not even be a new line so update the longest line
	if(lineLength > longestLine)
		longestLine = lineLength;

	//	Calculate the size of a single character
	size /= Vec2(longestLine, lines);
	float originX = position.x;

	for(auto c : str)
	{
		//	If the character is a newline, go on the next line
		if(c == '\n')
		{
			position.x = originX;
			position.y += size.y;

			continue;
		}

		//	Move the position forward and draw the character
		drawCharacter(c, font, position, size);
		position.x += size.x;
	}
}

Vec2 Frame::convert(Vec2 position)
{
	int w;
	int h;
	SDL_GetWindowSize(window, &w, &h);

	//	Move the point depending on where the camera is
	position -= cameraPosition;

	/*	Because the position can be negative, first make it positive by
	 *	adding the camera radius to it and then convert it to screen space */
	position += cameraRadius;
	position *= (Vec2(w, h) / cameraRadius);

	/*	If position is the same as the camera radius, 
	 *	position will have a value that is window size times 2.
	 *	To fix it just divide the position x and y by 2 */
	return Vec2(position.x / 2, position.y / 2);
}

}
