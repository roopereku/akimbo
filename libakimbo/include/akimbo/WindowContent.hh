#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/UpdatingEntity.hh>
#include <akimbo/RenderTarget.hh>

namespace akimbo
{

class WindowContent : public UpdatingEntity, public RenderTarget
{
public:

private:
	void onUpdate() override
	{
	}
};

}

#endif
