#ifndef AKIMBO_RENDER_HH
#define AKIMBO_RENDER_HH

#include "TextureAtlas.hh"
#include "Texture.hh"
#include "Vector2.hh"
#include "Vector3.hh"
#include "Shader.hh"
#include "Font.hh"

namespace Akimbo {
class Frame;

class Render
{
public:
	~Render();

	void color(float r, float g, float b, float a = 1.0f);
	void color(Vec3 value, float a = 1.0f);
	void color(int r, int g, int b, int a = 255) = delete;

	void clear();

	void fromAtlas(TextureAtlas& atlas, unsigned x, unsigned y, Vec2 position, Vec2 size);
	void texture(Texture& texture, Vec2 position, Vec2 size);

	void frame(Frame& frame, Vec2 position, Vec2 size);
	void box(Vec2 position, Vec2 size, bool filled);
	void line(Vec2 from, Vec2 to);
	void dot(Vec2 position);

	enum class TextMode
	{
		Overflow,
		Scroll,
		Wrap,
		Cut
	};

	//	Helpers so that the user doesn't need to type Akimbo::Render::TextMode::Wrap every time
	const TextMode cutText = TextMode::Cut;
	const TextMode wrapText = TextMode::Wrap;

	Vec2 text(const std::string& str, Font& font, Vec2 position, Vec2 size, TextMode mode = TextMode::Overflow);
	Vec2 text(const char* str, Font& font, Vec2 position, Vec2 size, TextMode mode = TextMode::Overflow);

	void fitText(const std::string& str, Font& font, Vec2 position, Vec2 size);

	const Vec2 topLeft;
	const Vec2 topRight;
	const Vec2 bottomLeft;
	const Vec2 bottomRight;
	const Vec2 center;
	const Vec2 radius;

	friend class Frame;

protected:
	//	Only Frame can create a Render object
	Render(Mat4& projection, float horizontalRadius);

	void character(char chr, Font& font, Vec2 position, Vec2 size);

	Mat4& projection;

	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;

private:
	void box(Shader& shader, Vec2 position, Vec2 size, bool filled);
};

}

#endif
