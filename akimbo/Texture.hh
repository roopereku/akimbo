#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include <string>

namespace Akimbo {

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	friend class Render;

protected:
	void initialize();
	unsigned int texture = 0;
};

}

#endif
