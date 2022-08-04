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

	Font(Font&& rhs);
	friend class Render;

protected:
	struct Character
	{
		Vec2 advance;
		Vec2 origin;
		Vec2 size;
		Vec2 uv;
	};

	unsigned texture;
	Character characters[95];
};

}

#endif
