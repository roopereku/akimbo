#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include <akimbo/Vector2.hh>

#include <memory>

namespace Akimbo
{

class TextureDetail
{
protected:
	Vec2i size;
};

class Texture
{
public:
	Texture() {}

	const TextureDetail& getDetail()
	{
		return *detail;
	}

	friend class Renderer;

private:
	Texture(std::shared_ptr <TextureDetail> detail)
		: detail(std::move(detail))
	{
	}

	std::shared_ptr <TextureDetail> detail;
};

}

#endif
