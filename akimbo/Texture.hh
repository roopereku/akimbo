#ifndef AKIMBO_TEXTURE_HH
#define AKIMBO_TEXTURE_HH

#include "Vector2.hh"

#include <string>

namespace Akimbo {

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	virtual Vec2 getAspectRatio() { return aspectRatio; }
	friend class Render;

protected:
	Vec2 aspectRatio;

	void initialize();
	unsigned int texture = 0;
};

}

#endif
