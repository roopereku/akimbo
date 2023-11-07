#ifndef AKIMBO_WINDOW_CONTENT_HH
#define AKIMBO_WINDOW_CONTENT_HH

#include <akimbo/UpdatingEntity.hh>
#include <akimbo/RenderTarget2D.hh>

namespace akimbo
{

class WindowContent : public UpdatingEntity, public RenderTarget2D
{
public:

private:
	void onUpdate() override
	{
	}
};

}

#endif
