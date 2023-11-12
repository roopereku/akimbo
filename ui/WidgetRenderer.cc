#include <akimbo/ui/WidgetRenderer.hh>
#include <akimbo/Window.hh>

namespace akimbo::UI
{

WidgetRenderer::WidgetRenderer(Renderer2D& renderer)
	: Renderer2D(renderer.getWindow()), renderer(renderer)
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
	renderer.clear(r, g, b, a);
}

void WidgetRenderer::clear()
{
	renderer.clear();
}

void WidgetRenderer::box(int x, int y, int w, int h)
{
	renderer.box(x, y, w, h);
}

void WidgetRenderer::line(int x1, int y1, int x2, int y2)
{
	renderer.line(x1, y1, x2, y2);
}

}
