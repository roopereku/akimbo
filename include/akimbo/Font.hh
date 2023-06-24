#ifndef AKIMBO_FONT_HH
#define AKIMBO_FONT_HH

#include <memory>

namespace Akimbo
{

class FontDetail
{
};

class Font
{
public:
	Font() {}

	operator bool()
	{
		return static_cast <bool> (detail);
	}

	const FontDetail& getDetail()
	{
		return *detail;
	}

	friend class Renderer;

private:
	Font(std::shared_ptr <FontDetail> detail)
		: detail(std::move(detail))
	{
	}

	std::shared_ptr <FontDetail> detail;
};

}

#endif
