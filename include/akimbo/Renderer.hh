#ifndef AKIMBO_RENDERER_HH
#define AKIMBO_RENDERER_HH

#include <akimbo/Module.hh>

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

	friend class Window;

private:
	virtual void render(RenderTarget& target)=0;
	virtual void onResize(unsigned w, unsigned h)=0;
};

}

#endif
