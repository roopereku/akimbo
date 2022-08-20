#ifndef AKIMBO_FONT_HH
#define AKIMBO_FONT_HH

#include "Vector2.hh"

#include <string>

namespace Akimbo {

class Font
{
public:
	Font(const std::string& path);
	~Font();

	friend class Render;

protected:
	struct Character
	{
		Vec2 advance;
		Vec2 origin;
		Vec2 size;

		Vec2 uv;
		Vec2 uvSize;
	};

	unsigned texture;
	Character& get(char ch);

	const char start = 32;
	const char end = 126;

private:
	Character characters[95];
};

}

#endif
