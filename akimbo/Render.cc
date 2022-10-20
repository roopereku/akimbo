#include "Matrix4.hh"
#include "Render.hh"
#include "Frame.hh"
#include "Debug.hh"
#include "Mesh.hh"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Akimbo {

Render::Render(Mat4& projection, float horizontalRadius)
	:	topLeft(-horizontalRadius, -1.0f), topRight(+horizontalRadius, -1.0f),
		bottomLeft(-horizontalRadius, +1.0f), bottomRight(+horizontalRadius, +1.0f),
		center(0.0f, 0.0f), radius(horizontalRadius, 1.0f), projection(projection)
{
}

Render::~Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST);
}

void Render::color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Render::clear()
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::fromAtlas(TextureAtlas& atlas, unsigned x, unsigned y, Vec2 position, Vec2 size)
{
	glBindTexture(GL_TEXTURE_2D, atlas.texture);
	Shader& shader = Shader::get(Shader::Preset::Atlas);

	shader.use();

	Vec2 tileStart = Vec2(x, y) / Vec2(atlas.horizontally, atlas.vertically);
	tileStart.y = 1.0f - tileStart.y;

	Vec2 tileEnd = tileStart + Vec2(1.0f, -1.0f) / Vec2(atlas.horizontally, atlas.vertically);

	shader.setVec2("start", tileStart);
	shader.setVec2("end", tileEnd);

	box(shader, position, size, true);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::texture(Texture& texture, Vec2 position, Vec2 size)
{
	glBindTexture(GL_TEXTURE_2D, texture.texture);
	box(Shader::get(Shader::Preset::Texture), position, size, true);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::frame(Frame& frame, Vec2 position, Vec2 size)
{
	//	FIXME allow color overlays for frames
	color(1.0f, 1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, frame.texture);
	box(Shader::get(Shader::Preset::Texture), position, size, true);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::box(Vec2 position, Vec2 size, bool filled)
{
	box(Shader::get(Shader::Preset::Color), position, size, true);
}

void Render::box(Shader& shader, Vec2 position, Vec2 size, bool filled)
{
	static Mesh square(Mesh::Shape::Square);

	position.y *= -1;
	size /= 2.0f;

	//	Position should determine the position of top left corner
	position += Vec2(size.x, -size.y);

	//	Create a transform that determines the position and scale
	Mat4 transform = glm::translate(projection, Vec3(position, 0.0f));
	transform = glm::scale(transform, Vec3(size, 1.0f));

	shader.use();
	shader.setColor(r, g, b, a);
	shader.setTransform(transform);

	square.draw();
}

void Render::line(Vec2 from, Vec2 to)
{
}

void Render::dot(Vec2 position)
{
}

void Render::character(char chr, Font& font, Vec2 position, Vec2 size)
{
	glBindTexture(GL_TEXTURE_2D, font.texture);

	Shader& shader = Shader::get(Shader::Preset::Text);
	shader.use();

	Font::Character& ch = font.get(chr);

	/*	This is a little cryptic but due to the way the
	 *	atlas shader calculates things, we need to flip
	 *	the beginning and ending Y positions for the UV positions */
	Vec2 uv(ch.uv.x, ch.uv.y + ch.uvSize.y);
	Vec2 uvEnd(ch.uv.x + ch.uvSize.x, ch.uv.y);

	shader.setVec2("start", uv);
	shader.setVec2("end", uvEnd);

	box(shader, position, size, true);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Vec2 Render::text(const char* str, Font& font, Vec2 position, Vec2 size, TextMode mode)
{
	//	If scrolling should be done, find the first visible character
	if(mode == TextMode::Scroll)
	{
		float x = 0.0f;

		for(size_t i = 0; str[i] != 0; i++)
		{
			const Font::Character& ch = font.get(str[i]);
			x += size.y * ch.advance;

			/*	FIXME
			 *	To implement perfect scrolling we need render partial characters.
			 *	Now the position is just shifted backwards which is fine when rendering
			 *	text that fills the entire framebuffer. The correct way to implement
			 *	this is first eliminating all the unnecessary characters and then
			 *	rendering partial versions of the first visible characters */
			if(x > size.x)
				position.x -= (size.y * ch.advance);
		}
	}

	//	FIXME With the font Comic.TTF the letter 'b' is too tall
	float maxWidth = size.y;
	const float baseline = size.y * font.baseline;

	Vec2 origin = position;
	float maxX = position.x;

	for(size_t i = 0; str[i] != 0; i++)
	{
		const char c = str[i];

		//	Handle line breaks
		if(c == '\n' || c == '\r')
		{
			maxX = std::max(position.x, maxX);
			position.y -= size.y;
			position.x = origin.x;

			continue;
		}

		const Font::Character& ch = font.get(c);
		const float advance = maxWidth * ch.advance;

		//	Has the text overflown the given area
		if(position.x + advance > origin.x + size.x)
		{
			//	Should the overflown text be cut?
			if(mode == TextMode::Cut)
				continue;

			//	Should the overflown text be placed on the next line?
			else if(mode == TextMode::Wrap)
			{
				maxX = std::max(position.x, maxX);
				position.y -= size.y;
				position.x = origin.x;
			}
		}

		const float chHeight = size.y * ch.sizeMultiplier.y;
		const float chWidth = maxWidth * ch.sizeMultiplier.x;

		//	Align the characters with each other on the baseline
		const float chBaseline = baseline - size.y * ch.baseline;
		Vec2 chPosition = position + Vec2(advance * ch.bearing.x, size.y - chHeight - chBaseline);

		character(c, font, chPosition, Vec2(chWidth, chHeight));
		position.x += advance;
	}

	maxX = std::max(position.x, maxX);
	position.y -= size.y;

	//	How much space the text actually took
	Vec2 end = Vec2(maxX, position.y);
	return end - origin;
}

Vec2 Render::text(const std::string& str, Font& font, Vec2 position, Vec2 size, TextMode mode)
{
	return text(str.c_str(), font, position, size, mode);
}

void Render::fitText(const std::string& str, Font& font, Vec2 position, Vec2 size)
{
	Vec2 overflow(0.0f, size.y);
	float maxX = overflow.x;

	//	Is the string larger than the given size
	for(auto c : str)
	{
		if(c == '\n' || c == '\r')
		{
			overflow.y += size.y;
			maxX = std::max(overflow.x, maxX);
			overflow.x = position.x;
			continue;
		}

		const Font::Character& ch = font.get(c);
		overflow.x += size.y * ch.advance;
	}

	//	What is the relation between the overflow and the given size
	maxX = std::max(overflow.x, maxX);
	Vec2 relation = Vec2(maxX, overflow.y) / size;
	relation.x = relation.x / relation.y;

	//	If necessary, adjust the size so that the string always fits
	if(relation.y > 1.0f) size.y /= relation.y;
	if(relation.x > 1.0f) size.y /= relation.x;

	text(str, font, position, size);
}

}
