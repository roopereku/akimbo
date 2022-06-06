#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include <string>

namespace Akimbo {

class Window;
class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	Texture(Texture&& rhs);
	friend class Frame;

protected:
};

}

#endif
