#ifndef AKIMBO_FONT_HH
#define AKIMBO_FONT_HH

#include "Vector2.hh"

#include <string>

namespace Akimbo {

enum class TextMode
{
	Overflow,
	Scroll,
	Wrap,
	Cut
};

enum class TextAlign
{
	Left,
	Right,
	Center,
};

class Font
{
public:
	Font(const std::string& path);
	~Font();

	friend class Render;

protected:
	struct Character
	{
		Vec2 uv;
		Vec2 uvSize;

		Vec2 bearing;
		Vec2 sizeMultiplier;

		float advance;
		float baseline;
	};

	float baseline = 0.0f;

	unsigned texture;
	Character& get(char ch);

	const char start = 32;
	const char end = 126;

private:
	Character characters[95];
};

}

#endif
