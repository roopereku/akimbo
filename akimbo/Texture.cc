#include "Texture.hh"
#include "Window.hh"
#include "Debug.hh"

namespace Akimbo {

static unsigned textures = 0;

Texture::Texture(const std::string& path)
{
	DBG_LOG("Loading image '%s'", path.c_str());
}

Texture::~Texture()
{
}

Texture::Texture(Texture&& rhs)// : texture(rhs.texture)
{
	//rhs.texture = NULL;
}

}
