#ifndef AKIMBO_RENDER_TARGET_HH
#define AKIMBO_RENDER_TARGET_HH

namespace akimbo
{

class RenderTarget
{
public:
	bool isDirty()
	{
		return dirty;
	}

	void clear()
	{
		dirty = false;
	}

	void render()
	{
		dirty = true;
	}

private:
	bool dirty = false;
};

}

#endif
