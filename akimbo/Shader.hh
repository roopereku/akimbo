#ifndef AKIMBO_SHADER_HH
#define AKIMBO_SHADER_HH

#include "Matrix4.hh"
#include "Vector2.hh"

#include <string>

namespace Akimbo {

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();

	void setTransform(const Mat4& transform);
	void setColor(float r, float g, float b, float a = 1.0f);
	void setVec2(const char* which, Vec2 value);

	enum class Preset
	{
		Texture,
		Atlas,
		Color,
		Text
	};

	static Shader& get(Preset preset);

private:
	unsigned loadShader(const std::string& path, bool isVertex);

	unsigned id = 0;
	unsigned transformLocation = 0;
	unsigned colorLocation = 0;
};

}

#endif
