#include "Shader.hh"

#include "glm/gtc/type_ptr.hpp"
#include <SDL2/SDL_log.h>
#include <GL/glew.h>

#include <fstream>

namespace Akimbo {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	unsigned vertex = loadShader(vertexPath, true);
	unsigned fragment = loadShader(fragmentPath, false);

	if(!vertex || !fragment)
		return;

	id = glCreateProgram();
	int success;

	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success)
	{
		char log[512];
		glGetProgramInfoLog(id, 512, NULL, log);
		printf("Error linking shader compiled from '%s' and '%s': %s\n", vertexPath.c_str(), fragmentPath.c_str(), log);

		return;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	transformLocation = glGetUniformLocation(id, "transform");
	colorLocation = glGetUniformLocation(id, "color");

	use();
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::setTransform(const Mat4& transform)
{
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
}

void Shader::setColor(float r, float g, float b, float a)
{
	glUniform4f(colorLocation, r, g, b, a);
}

void Shader::setVec2(const char* which, Vec2 value)
{
	unsigned location = glGetUniformLocation(id, which);
	glUniform2f(location, value.x, value.y);
}

void Shader::use()
{
	glUseProgram(id);
}

unsigned Shader::loadShader(const std::string& path, bool isVertex)
{
	std::ifstream file(path);

	if(!file)
	{
		SDL_Log("Couldn't open '%s'", path.c_str());
		return -1;
	}

	std::string data;
	std::string line;

	while(getline(file, line))
		data += line + '\n';

	file.close();

	unsigned shader = glCreateShader(isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	char* source = const_cast <char*> (data.data());

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, NULL, log);
		SDL_Log("Error compiling '%s': %s\n", path.c_str(), log);
		return 0;
	}

	return shader;
}

Shader& Shader::get(Preset preset)
{
	static Shader presets[]
	{
		Shader("resources/shaders/generic.vs", "resources/shaders/texture.fs"),
		Shader("resources/shaders/atlas.vs", "resources/shaders/texture.fs"),
		Shader("resources/shaders/generic.vs", "resources/shaders/color.fs"),
		Shader("resources/shaders/generic.vs", "resources/shaders/text.fs")
	};

	//	TODO call use() here
	return presets[static_cast <size_t> (preset)];
}

}
