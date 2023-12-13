#include <akimbo/ui/WidgetRenderer.hh>
#include <akimbo/Window.hh>

#include <cmath>

namespace akimbo::UI
{

WidgetRenderer::WidgetRenderer(Renderer2D& renderer, std::weak_ptr <Widget> target, Vec2i offset)
	: Renderer2D(renderer), renderer(renderer), target(target), offset(offset)
{
	Vec2i previousOrigin = renderer.getOrigin();

	// To make sure that the scissor doesn't go outside the parent layout,
	// make sure that the new origin doesn't go beyond the parent origin.
	origin = Vec2i(
		std::max(previousOrigin.x, previousOrigin.x + offset.x),
		std::max(previousOrigin.y, previousOrigin.y + offset.y)
	);

	const auto targetSize = target.lock()->size();
	renderer.setScissor(origin.x, origin.y, targetSize.x, targetSize.y);
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
	const auto targetSize = target.lock()->size();

	renderer.color(r, g, b, a);
	renderer.box(offset.x, offset.y, targetSize.x, targetSize.y);
}

void WidgetRenderer::clear()
{
	const auto targetSize = target.lock()->size();
	renderer.box(offset.x, offset.y, targetSize.x, targetSize.y);
}

void WidgetRenderer::box(int x, int y, int w, int h, bool filled)
{
	renderer.box(offset.x + x, offset.y + y, w, h, filled);
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

void WidgetRenderer::showBorders()
{
	const auto targetSize = target.lock()->size();

	renderer.color(1.0f, 1.0f, 1.0f);
	line(0, 0, targetSize.x, targetSize.y);
}

Vec2i WidgetRenderer::getOrigin()
{
	return origin;
}

}
