#include <akimbo/ui/WidgetRenderer.hh>
#include <akimbo/Window.hh>

namespace akimbo::UI
{

WidgetRenderer::WidgetRenderer(Renderer2D& renderer, Widget& target, Vec2i offset)
	: Renderer2D(renderer.getWindow()), renderer(renderer), target(target), offset(offset)
{
}

void WidgetRenderer::color(float r, float g, float b, float a)
{
	renderer.color(r, g, b, a);
}

void WidgetRenderer::setScissor(int x, int y, int w, int h)
{
	renderer.setScissor(x, y, w, h);
}

void WidgetRenderer::display()
{
	renderer.display();
}

void WidgetRenderer::clear(float r, float g, float b, float a)
{
	renderer.color(r, g, b, a);
	renderer.box(offset.x, offset.y, target.size().x, target.size().y);
}

void WidgetRenderer::clear()
{
	renderer.box(offset.x, offset.y, target.size().x, target.size().y);
}

void WidgetRenderer::box(int x, int y, int w, int h)
{
	renderer.box(offset.x + x, offset.y + y, w, h);
}

void WidgetRenderer::line(int x1, int y1, int x2, int y2)
{
	renderer.line(
		offset.x + x1,
		offset.y + y1,
		offset.x + x2,
		offset.y + y2
	);
}

}
