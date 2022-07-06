#ifndef AKIMBO_RENDER_HH
#define AKIMBO_RENDER_HH

#include "Texture.hh"
#include "Vector2.hh"
#include "Shader.hh"
#include "Font.hh"

namespace Akimbo {
class Frame;

class Render
{
public:
	~Render();

	void color(float r, float g, float b, float a = 1.0f);
	void color(int r, int g, int b, int a = 255) = delete;

	void clear();

	void texture(Texture& texture, Vec2 position, Vec2 size);
	void frame(Frame& frame, Vec2 position, Vec2 size);
	void box(Vec2 position, Vec2 size, bool filled);
	void line(Vec2 from, Vec2 to);
	void dot(Vec2 position);

	void character(char chr, Font& font, Vec2 position, Vec2 size);
	void text(const std::string& str, Font& font, Vec2 position, Vec2 size);

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

	Mat4& projection;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;

private:
	void box(Shader& shader, Vec2 position, Vec2 size, bool filled);
};

}

#endif
