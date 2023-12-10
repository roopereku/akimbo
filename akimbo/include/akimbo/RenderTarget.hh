#ifndef AKIMBO_RENDER_TARGET_HH
#define AKIMBO_RENDER_TARGET_HH

namespace akimbo
{

class RenderTarget
{
public:
	void clear();
	bool isDirty();
	void render();

private:
	bool dirty = false;
};

}

#endif
