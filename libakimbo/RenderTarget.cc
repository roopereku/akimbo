#include <akimbo/RenderTarget.hh>

namespace akimbo
{

bool RenderTarget::isDirty()
{
	return dirty;
}

void RenderTarget::clear()
{
	dirty = false;
}

void RenderTarget::render()
{
	dirty = true;
}

}
