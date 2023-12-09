#include <akimbo/ui/Root.hh>
#include <akimbo/ui/Layout.hh>
#include <akimbo/Renderer2D.hh>
#include <akimbo/Core.hh>

namespace akimbo::UI
{

Root::Root(Layout& layout) : layout(layout)
{
	addRepeatingTask([this]()
	{
		// UI Root is rendered constantly to make it easy to
		// render the root layout.
		render();
	});
}

Root::~Root()
{
}

Root& Root::add(Layout& layout)
{
	return getCore().add(new Root(layout));
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

void Root::onAttached()
{
	layout.size = window.getValue().size();
}

void Root::onMouseClick(Vec2i at)
{
	focused = layout.findAt(at);

	if(focused)
	{
		focused->onClick(at);
	}
}

void Root::onMouseDrag(Vec2i delta)
{
}

}
