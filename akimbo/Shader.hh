#ifndef AKIMBO_SHADER_HH
#define AKIMBO_SHADER_HH

#include "Matrix4.hh"

#include <string>

namespace Akimbo {

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();

	void setTransform(const Mat4& transform);

private:
	unsigned loadShader(const std::string& path, bool isVertex);

	unsigned id = 0;
	unsigned transformLocation = 0;
};

}

#endif
