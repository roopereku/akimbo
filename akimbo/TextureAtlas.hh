#ifndef AKIMBO_TEXTURE_ATLAS_HH
#define AKIMBO_TEXTURE_ATLAS_HH

#include "Texture.hh"

namespace Akimbo {

class TextureAtlas : public Texture
{
public:
	TextureAtlas(const std::string& path, unsigned horizontally, unsigned vertically);
	friend class Render;

protected:
	unsigned horizontally;
	unsigned vertically;
};

}

#endif
