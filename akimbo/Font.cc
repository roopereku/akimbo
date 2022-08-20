#include "Window.hh"
#include "Debug.hh"
#include "Font.hh"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Akimbo {

static unsigned fontsLoaded = 0;

Font::Font(const std::string& path)
{
	static FT_Library ft;

	if(fontsLoaded == 0)
	{
		DBG_LOG("Initializing Freetype2");

		if(FT_Init_FreeType(&ft))
		{
			fprintf(stderr, "Unable to init Freetype2\n");
			return;
		}
	}

	DBG_LOG("Loading font '%s'", path.c_str());

	FT_Face face;

	if(FT_New_Face(ft, path.c_str(), 0, &face))
	{
		fprintf(stderr, "Unable to load font '%s'\n", path.c_str());
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	FT_GlyphSlot g = face->glyph;

	unsigned w = 0;
	unsigned h = 0;

	unsigned roww = 0;
	unsigned rowh = 0;

	/*	FIXME somehow figure out the width and the height beforehand
	 *	so that FT_Load_Char can be called only once per character */

	for(char c = start; c <= end; c++)
	{
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			fprintf(stderr, "Unable to load character '%c' from font '%s'\n", c, path.c_str());
			return;
		}

		if(roww + g->bitmap.width + 1 >= 1024)
		{
			w = std::max(w, roww);
			h += rowh;
			roww = 0;
			rowh = 0;
		}

		roww += g->bitmap.width + 1;
		rowh = std::max(rowh, g->bitmap.rows);
	}

	w = std::max(w, roww);
	h += rowh;

	DBG_LOG("width %u", w);
	DBG_LOG("height %u", h);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned x = 0;
	Character* current = characters;

	int ox = 0;
	int oy = 0;
	rowh = 0;

	for(char c = start; c <= end; c++)
	{
		if(FT_Load_Char(face, c, FT_LOAD_RENDER))
			return;

		if(ox + g->bitmap.width + 1 >= 1024)
		{
			oy += rowh;
			rowh = 0;
			ox = 0;
		}

		glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy,
						g->bitmap.width, g->bitmap.rows, GL_RED,
						GL_UNSIGNED_BYTE, g->bitmap.buffer);

		current->advance = Vec2(g->advance.x >> 6, g->advance.y >> 6);
		current->size = Vec2(g->bitmap.width, g->bitmap.rows);
		current->origin = Vec2(g->bitmap_left, g->bitmap_top);
		current->uv = Vec2(static_cast <float> (ox) / w, static_cast<float> (oy) / h);
		current->uvSize = current->size / Vec2(w, h);

		DBG_LOG("%c uv %.2f %.2f", c, current->uv.x, current->uv.y);
		DBG_LOG("%c uvSize %.2f %.2f", c, current->uvSize.x, current->uvSize.y);

		rowh = std::max(rowh, g->bitmap.rows);
		ox += g->bitmap.width + 1;

		current++;
	}

	fontsLoaded++;
}

Font::~Font()
{
	if(--fontsLoaded == 0)
	{
	}
}

Font::Character& Font::get(char ch)
{
	return characters[ch - start];
}

}
