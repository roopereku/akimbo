#include <akimbo/Renderer.hh>
#include <SDL2/SDL_log.h>

namespace Akimbo
{

Texture Renderer::createTexture(std::string_view path)
{
	auto it = textureCache.find(path);

	// If the given path hasn't been loaded, load it.
	if(it == textureCache.end())
	{
		SDL_Log("Loaded texture '%s'", path.data());
		return Texture(textureCache.insert(std::make_pair(path, initTexture(path))).first->second);
	}

	// Return the cached texture if it's been loaded previously.
	return Texture(it->second);
}

Font Renderer::createFont(std::string_view path)
{
	auto it = fontCache.find(path);

	// If the given path hasn't been loaded, load it.
	if(it == fontCache.end())
	{
		auto ret = initFont(path);
		SDL_Log("Loaded font '%s'", path.data());

		fontCache[path] = ret;
		return ret;
	}

	SDL_Log("Return cached font '%s'", path.data());
	// Return the cached font if it's been loaded previously.
	return Font(it->second);
}

}
