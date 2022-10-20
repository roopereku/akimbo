#include "TextureAtlas.hh"
#include "Debug.hh"

namespace Akimbo {

TextureAtlas::TextureAtlas(const std::string& path, unsigned horizontally, unsigned vertically)
	: Texture(path), horizontally(horizontally), vertically(vertically)
{
	DBG(
		if(texture != 0)
		{
			DBG_LOG("Created texture atlas '%s' %u x %u", path.c_str(), horizontally, vertically);
		}

		else
		{
			DBG_LOG("Failed to create texture atlas '%s'", path.c_str());
		}
	);

	//	Calculate the aspect ratio of a single texture in the texture atlas
	float atlasAspectRatio = static_cast <float> (horizontally) / vertically;
	aspectRatio.x = aspectRatio.x / atlasAspectRatio;
}

}
