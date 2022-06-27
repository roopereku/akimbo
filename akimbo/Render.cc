#include "Matrix4.hh"
#include "Render.hh"
#include "Frame.hh"
#include "Mesh.hh"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Akimbo {

Render::Render(Mat4& projection, float horizontalRadius)
	:	topLeft(-horizontalRadius, 1.0f), topRight(+horizontalRadius, 1.0f),
		bottomLeft(-horizontalRadius, -1.0f), bottomRight(+horizontalRadius, -1.0f),
		center(0.0f, 0.0f), radius(horizontalRadius, 1.0f), projection(projection)
{
}

Render::~Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	Shader::get(Shader::Preset::Color).use();
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

void Render::frame(Frame& frame, Vec2 position, Vec2 size)
{
	glBindTexture(GL_TEXTURE_2D, frame.texture);
	box(Shader::get(Shader::Preset::Texture), position, size, true);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::box(Vec2 position, Vec2 size, bool filled)
{
	Shader& colorShader = Shader::get(Shader::Preset::Color);

	colorShader.use();
	colorShader.setColor(r, g, b, a);

	box(colorShader, position, size, true);
}

void Render::box(Shader& shader, Vec2 position, Vec2 size, bool filled)
{
	static Mesh square(Mesh::Shape::Square);

	size /= 2.0f;

	//	Position should determine the position of top left corner
	position += Vec2(size.x, -size.y);

	//	Create a transform that determines the position and scale
	Mat4 transform = glm::translate(projection, Vec3(position, 0.0f));
	transform = glm::scale(transform, Vec3(size, 1.0f));

	shader.use();
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
}

void Render::text(const std::string& str, Font& font, Vec2 position, Vec2 size)
{
}

}
