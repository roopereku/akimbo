#include <akimbo/ui/Root.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

Root::Root(Layout& layout) : layout(layout)
{
}

Root::~Root()
{
}

Root& Root::add(Layout& layout)
{
	return getCore().addUpdating(new Root(layout));
}

Root::operator Layout&()
{
	return layout;
}

void Root::onRender(Renderer2D& render)
{
	render.clear(0.3f, 0.3f, 0.3f);
	layout.onRender(render);
}

void Root::onUpdate()
{
	// UI Root is rendered constantly to make it easy to
	// render the root layout.
	render();
}

}
