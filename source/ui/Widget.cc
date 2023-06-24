#include <akimbo/ui/Widget.hh>
#include <SDL2/SDL_log.h>

namespace Akimbo::UI
{

void Widget::onRender(Render2D& render)
{
	render.color(1.0f, 1.0f, 1.0f);
	render.clear();
}

void Widget::onAttached()
{
	defaultFont = getRenderer().createFont("/usr/share/fonts/TTF/Arial.TTF");
	onLoadResources();
}

}
