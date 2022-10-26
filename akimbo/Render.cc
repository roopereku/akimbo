#include "Matrix4.hh"
#include "Render.hh"
#include "Frame.hh"
#include "Debug.hh"
#include "Mesh.hh"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Akimbo {

Render::Render(Mat4& projection) : projection(projection)
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

void Render::color(Vec3 value, float a)
{
	color(value.r, value.g, value.b, a);
}

void Render::clear()
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::fromAtlas(TextureAtlas& atlas, unsigned x, unsigned y, Vec2 position, Vec2 size)
{
	/*	FIXME
	 *	Since the Y axis was flipped, it broke the original texture atlas code.
	 *	This y++ is here because the breakage was mostly that y was 1 too little */
	y++;

	glBindTexture(GL_TEXTURE_2D, atlas.texture);
	Shader& shader = Shader::get(Shader::Preset::Atlas);

	shader.use();

	Vec2 tileStart = Vec2(x, y) / Vec2(atlas.horizontally, atlas.vertically);
	tileStart.y = -tileStart.y;

	Vec2 tileEnd = tileStart + Vec2(1.0f, 1.0f) / Vec2(atlas.horizontally, atlas.vertically);

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

Vec2 Render::text(const char* str, size_t count, Font& font, Vec2 position, Vec2 size, TextMode mode)
{
	//	If scrolling should be done, find the first visible character
	if(mode == TextMode::Scroll)
	{
		float x = 0.0f;

		for(size_t i = 0; i < count; i++)
		{
			const Font::Character& ch = font.get(str[i]);
			x += size.y * ch.advance;

			/*	FIXME
			 *	To implement perfect scrolling we need render partial characters.
			 *	Now the position is just shifted backwards which is fine when rendering
			 *	text that fills the entire framebuffer. The correct way to implement
			 *	this is first eliminating all the unnecessary characters and then
			 *	rendering partial versions of the first visible characters
			 *
			 *	Maybe glScissor is a good fix for this	*/
			if(x > size.x)
				position.x -= (size.y * ch.advance);
		}
	}

	//	FIXME With the font Comic.TTF the letter 'b' is too tall
	float maxWidth = size.y;
	const float baseline = size.y * font.baseline;

	Vec2 origin = position;
	float maxX = position.x;

	for(size_t i = 0; i < count; i++)
	{
		const char c = str[i];

		//	Handle line breaks
		if(c == '\n' || c == '\r')
		{
			maxX = std::max(position.x, maxX);
			position.y += size.y;
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
				position.y += size.y;
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
	position.y += size.y;

	//DBG_LOG("text maxX %.2f", maxX - origin.x);

	//	How much space the text actually took
	Vec2 end = Vec2(maxX, position.y);
	return end - origin;
}

Vec2 Render::text(const char* str, Font& font, Vec2 position, Vec2 size, TextMode mode)
{
	size_t l = 0;
	while(str[l] != 0) l++;
	return text(str, l, font, position, size, mode);
}

Vec2 Render::text(const std::string& str, Font& font, Vec2 position, Vec2 size, TextMode mode)
{
	return text(str.c_str(), str.size(), font, position, size, mode);
}

void Render::centerText(const char* str, Font& font, Vec2 position, Vec2 size, TextAlign align)
{
	fitText(str, font, position, size, align, true);
}

void Render::centerText(const std::string& str, Font& font, Vec2 position, Vec2 size, TextAlign align)
{
	fitText(str.c_str(), font, position, size, align, true);
}

void Render::fitText(const std::string& str, Font& font, Vec2 position, Vec2 size, TextAlign align, bool center)
{
	fitText(str.c_str(), font, position, size, align, center);
}

void Render::fitText(const char* str, Font& font, Vec2 position, Vec2 size, TextAlign align, bool center)
{
	Vec2 overflow(0.0f, size.y);
	float maxX = overflow.x;
	unsigned rows = 1;

	//	Find out how much spaces the text takes
	for(size_t i = 0; str[i] != 0; i++)
	{
		if(str[i] == '\n' || str[i] == '\r')
		{
			maxX = std::max(overflow.x, maxX);
			overflow.y += size.y;
			overflow.x = 0.0f;
			rows++;

			continue;
		}

		const Font::Character& ch = font.get(str[i]);
		overflow.x += size.y * ch.advance;
	}

	overflow.x = std::max(overflow.x, maxX);
	float originalY = size.y;

	//	What is the relation between the overflow and the given size
	Vec2 relation = overflow / size;
	Vec2 adjustment(0.0f, 0.0f);

	//	Adjust the size so that the text always fits horizontally
	size.y /= relation.y;
	float x = overflow.x / relation.y;

	/*	Calculate a value which tells if the text needs to be scaled
	 *	down when it can't fit horizontally on the screen */
	relation.x = relation.x / relation.y;

	//	If the text can't fit horizontally on the screen, do adjustments
	if(relation.x > 1.0f)
	{
		size.y /= relation.x;
		x = x / relation.x;
	}

	//	How much space will the longest line text actually take
	Vec2 maxSize = Vec2(x, size.y);

	//	Should the text be centered
	if(center)
	{
		maxX = (1.0f - relation.x) / 2.0f;

		//	If the text should be centered horizontally, set the adjustment
		if(maxX >= 0.0f)
			adjustment.x = size.x * maxX;

		//	If the text should be centered vertically, set the adjustment
		if(relation.x > 1.0f)
			adjustment.y = originalY / 2 - (maxSize.y * rows) / 2;
	}

	//	If text isn't centered and is aligned on the left, it can just be rendered without extra processing
	else if(align == TextAlign::Left)
	{
		text(str, font, position, size);
		return;
	}

	//	The text alignment can be achieved by multiplying a shift with one of these values
	float shiftMultiplier;
	switch(align)
	{
		case TextAlign::Center: shiftMultiplier = 0.5f; break;
		case TextAlign::Right: shiftMultiplier = 1.0f; break;
		case TextAlign::Left: shiftMultiplier = 0.0f; break;
	}

	overflow.x = 0.0f;
	const char* start = str;

	/*	Now that we know where the text offset is and how much space
	 *	the longest line takes, we need to recalculate how much
	 *	space each line takes horizontally relative to the new height. */
	for(size_t i = 0; true; i++)
	{
		/*	If there's a line break or the string ends, calculate how much
		 *	the text should be shifted forwards and render a portion
		 *	of the text that appears before the break */
		if(str[i] == '\n' || str[i] == 0 || str[i] == '\r')
		{
			//	How many character are in this portion of the text
			size_t count = &str[i] - start;

			//	Calculate the size and shift of the portion
			Vec2 portionSize(overflow.x, maxSize.y);
			Vec2 shift((maxSize.x - portionSize.x) * shiftMultiplier, 0.0f);

			text(start, count, font, position + adjustment + shift, portionSize);

			position.y += size.y;
			start = &str[i + 1];
			overflow.x = 0.0f;

			if(str[i] == 0) break;
			continue;
		}

		const Font::Character& ch = font.get(str[i]);
		overflow.x += maxSize.y * ch.advance;
	}
}

}
