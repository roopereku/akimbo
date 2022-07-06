#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include <string>

namespace Akimbo {

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	Texture(Texture&& rhs);
	friend class Render;

protected:
	unsigned int texture;
};

}

#endif
