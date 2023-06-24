#ifndef AKIMBO_RENDERER_HH
#define AKIMBO_RENDERER_HH

#include <akimbo/Module.hh>
#include <akimbo/Texture.hh>
#include <akimbo/Font.hh>

#include <unordered_map>
#include <string_view>
#include <memory>

namespace Akimbo
{

class Render
{
public:
};

class RenderTarget : public Module
{
public:
	void render()
	{
		dirty = true;
	}

	bool popDirty()
	{
		bool ret = dirty;
		dirty = false;
		return ret;
	}

private:
	bool dirty = false;
};

class Renderer
{
public:
	virtual ~Renderer() {}

	Texture createTexture(std::string_view path);
	Font createFont(std::string_view path);

	friend class Window;

protected:
	virtual std::shared_ptr <TextureDetail> initTexture(std::string_view path)=0;
	virtual std::shared_ptr <FontDetail> initFont(std::string_view path)=0;

private:
	virtual void render(RenderTarget& target)=0;
	virtual void onResize(unsigned w, unsigned h)=0;

	std::unordered_map <std::string_view, std::shared_ptr <TextureDetail>> textureCache;
	std::unordered_map <std::string_view, std::shared_ptr <FontDetail>> fontCache;
};

}

#endif
