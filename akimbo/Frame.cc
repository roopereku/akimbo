#include "Matrix4.hh"
#include "Frame.hh"
#include "Debug.hh"
#include "Mesh.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_log.h>
#include <GL/glew.h>

namespace Akimbo {

Frame::Frame() : shader("akimbo/shaders/test.vs", "akimbo/shaders/test.fs")
{
	transform.scale(0.5f, 0.5f, 1.0f);
	resize(Vec2i(540, 960));
}

Frame::~Frame()
{
	clearBuffers();
}

void Frame::clearBuffers()
{
	//	Delete the buffers if they exist
	if(texture > 0) glDeleteTextures(1, &texture);
	if(rbo > 0) glDeleteRenderbuffers(1, &fbo);
	if(fbo > 0) glDeleteFramebuffers(1, &fbo);

	//	Null them just in case
	texture = 0;
	rbo = 0;
	fbo = 0;
}

void Frame::resize(Vec2i size)
{
	clearBuffers();

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		SDL_Log("Framebuffer not complete");
		return;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Render Frame::render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST);

	return Render(shader);
}

void Frame::draw()
{
	static Mesh square(Mesh::Shape::Square);

	shader.use();

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.setTransform(transform.transform);

	glBindTexture(GL_TEXTURE_2D, texture);
	square.draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
