#include <akimbo/Renderer.hh>

namespace Akimbo
{

Texture Renderer::createTexture(std::string_view path)
{
	auto it = textureCache.find(path);

	// If the given path hasn't been loaded, load it.
	if(it == textureCache.end())
		return Texture(textureCache.insert(std::make_pair(path, initTexture(path))).first->second);

	// Return the cached texture if it's been loaded previously.
	return Texture(it->second);
}

}
