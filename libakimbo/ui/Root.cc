#include <akimbo/ui/Root.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

Root& Root::add()
{
	return getCore().addUpdating(new Root);
}

void Root::onRender(Renderer2D& render)
{
	render.clear(0.5f, 0.5f, 0.5f);
}

}
