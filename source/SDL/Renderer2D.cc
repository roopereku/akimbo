#include <akimbo/SDL/Renderer2D.hh>
#include <akimbo/SDL/TextureDetail.hh>
#include <akimbo/SDL/FontDetail.hh>
#include <SDL2/SDL_log.h>

#include <cassert>

namespace Akimbo::SDL
{

Render2D::Render2D(SDL_Renderer* renderer, Vec2i offset, Vec2i screenSize)
	: renderer(renderer), offset(offset), screenSize(screenSize)
{
	overlays.push_back({ offset.x, offset.y, screenSize.x, screenSize.y });
}

void Render2D::color(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, a * 255);
}

void Render2D::clear()
{
	box(Vec2(0, 0), Vec2(1, 1));
}

void Render2D::box(Vec2 position, Vec2 size)
{
	Vec2i boxPosition(
		position.x * screenSize.x,
		position.y * screenSize.y
	);

	Vec2i boxSize(
		size.x * screenSize.x,
		size.y * screenSize.y
	);

	box(boxPosition, boxSize);
}

void Render2D::box(Vec2i position, Vec2i size)
{
	SDL_Rect r
	{
		offset.x + position.x,
		offset.y + position.y,
		size.x,
		size.y
	};

	SDL_RenderFillRect(renderer, &r);
}

void Render2D::texture(Vec2 position, Vec2 size, Texture& tex)
{
	Vec2i texturePosition(
		position.x * screenSize.x,
		position.y * screenSize.y
	);

	Vec2i textureSize(
		size.x * screenSize.x,
		size.y * screenSize.y
	);

	texture(texturePosition, textureSize, tex);
}

void Render2D::texture(Vec2i position, Vec2i size, Texture& tex)
{
	SDL_Rect r
	{
		offset.x + position.x,
		offset.y + position.y,
		size.x,
		size.y
	};

	const auto& detail = static_cast <const SDL::TextureDetail&> (tex.getDetail());
	SDL_RenderCopy(renderer, detail.texture, NULL, &r);
}

void Render2D::text(Vec2 position, Vec2 size, Font& font, std::string_view str)
{
	Vec2i textPosition(
		position.x * screenSize.x,
		position.y * screenSize.y
	);

	Vec2i textSize(
		size.x * screenSize.x,
		size.y * screenSize.y
	);

	text(textPosition, textSize, font, str);
}

void Render2D::text(Vec2i position, Vec2i size, Font& font, std::string_view str)
{
	assert(static_cast <bool> (font));

	SDL_Rect r
	{
		offset.x + position.x,
		offset.y + position.y,
		size.x,
		size.y
	};

	//color(0.5f, 0, 0);
	//box(position, size);

	const auto& detail = static_cast <const SDL::FontDetail&> (font.getDetail());
	int origin = r.x;

	for(auto c : str)
	{
		const FontDetail::GlyphData& glyph = detail.glyphs.at(c);

		SDL_Rect part
		{
			glyph.atlasOffset,
			0,
			glyph.advance,
			detail.atlasSize.y
		};

		r.w = glyph.advance;
		if(r.x + r.w > origin + size.x)
			break;

		SDL_RenderCopy(renderer, detail.atlas, &part, &r);
		r.x += glyph.advance;
	}
}

void Render2D::target(Vec2 position, Vec2 size, RenderTarget2D& rt)
{
	Vec2i targetOffset(
		position.x * screenSize.x,
		position.y * screenSize.y
	);

	Vec2i targetSize(
		size.x * screenSize.x,
		size.y * screenSize.y
	);

	target(targetOffset, targetSize, rt);
}

void Render2D::target(Vec2i position, Vec2i size, RenderTarget2D& rt)
{
	position.x += offset.x;
	position.y += offset.y;

	SDL_Rect clipRect = { offset.x, offset.y, screenSize.x, screenSize.y };
	SDL_RenderSetClipRect(renderer, &clipRect);

	Render2D render(renderer, position, size);
	rt.onRender(render);

	SDL_RenderSetClipRect(renderer, &clipRect);
	overlays.insert(overlays.end(), render.overlays.begin(), render.overlays.end());
}

Renderer2D::Renderer2D(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer2D::~Renderer2D()
{
	if(renderer)
		SDL_DestroyRenderer(renderer);
}

std::shared_ptr <Akimbo::TextureDetail> Renderer2D::initTexture(std::string_view path)
{
	return std::make_shared <SDL::TextureDetail> (renderer, path);
}

std::shared_ptr <Akimbo::FontDetail> Renderer2D::initFont(std::string_view path)
{
	return std::make_shared <SDL::FontDetail> (renderer, path);
}

void Renderer2D::render(RenderTarget& target)
{
	Render2D render(renderer, Vec2i(0, 0), screenSize);
	static_cast <RenderTarget2D&> (target).onRender(render);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for(auto& overlay : render.overlays)
		SDL_RenderDrawRect(renderer, &overlay);

	SDL_RenderPresent(renderer);
}

void Renderer2D::onResize(unsigned w, unsigned h)
{
	screenSize.x = w;
	screenSize.y = h;
}

}
