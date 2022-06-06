#ifndef AKIMBO_FONT_HH
#define AKIMBO_FONT_HH

#include "Vector2.hh"

#include <string>

namespace Akimbo {

class Window;
class Font
{
public:
	Font(const std::string& path);
	~Font();

	Font(Font&& rhs);
	friend class Frame;

protected:
};

}

#endif
