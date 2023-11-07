#ifndef AKIMBO_RENDER_TARGET_HH
#define AKIMBO_RENDER_TARGET_HH

namespace akimbo
{

class RenderTarget
{
public:

protected:
	void render()
	{
		isDirty = true;
	}

private:
	bool isDirty = false;
};

}

#endif
