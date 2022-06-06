#include "Window.hh"
#include "Debug.hh"
#include "Font.hh"

namespace Akimbo {

Font::Font(const std::string& path)
{
	DBG_LOG("Loading font '%s'", path.c_str());
}

Font::~Font()
{
}

Font::Font(Font&& rhs)
{
}

}
