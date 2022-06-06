#ifndef AKIMBO_RENDER_HH
#define AKIMBO_RENDER_HH

#include "Vector2.hh"
#include "Shader.hh"
#include "Font.hh"

namespace Akimbo {
class Render
{
public:
	~Render();

	void color(float r, float g, float b, float a = 1.0f);
	void color(int r, int g, int b, int a = 255) = delete;

	void clear();

	void box(Vec2 position, Vec2 size, bool filled);
	void line(Vec2 from, Vec2 to);
	void dot(Vec2 position);

	void character(char chr, Font& font, Vec2 position, Vec2 size);
	void text(const std::string& str, Font& font, Vec2 position, Vec2 size);

	friend class Frame;

protected:
	//	Only Frame can create a Render object
	Render(Shader& shader);
	Shader& shader;

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;
};

}

#endif
