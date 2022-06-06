#include "Matrix4.hh"
#include "Render.hh"
#include "Mesh.hh"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Akimbo {

Render::Render(Shader& shader) : shader(shader)
{
	shader.use();
}

Render::~Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
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

void Render::box(Vec2 position, Vec2 size, bool filled)
{
	static Mesh square(Mesh::Shape::Square);

	Mat4 transform = glm::translate(Mat4(1.0f), Vec3(position, 0.0f));
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
