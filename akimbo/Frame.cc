#include "Matrix4.hh"
#include "Frame.hh"
#include "Debug.hh"
#include "Mesh.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_log.h>
#include <GL/glew.h>

namespace Akimbo {

Frame::Frame()
{
	/*	800x800 is a good reference size where (-1.0, 1.0) is the
	 *	top-left corner when the projection is applied */
	resize(Vec2i(800, 800));
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
	//DBG_LOG("Creating framebuffer of size %d %d", size.x, size.y);

	clearBuffers();

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//	Create a texture to draw onto
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	Attach the texture to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	//	Create a renderbuffer
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//	Attach the renderbuffer to the framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	GLenum res = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if(res != GL_FRAMEBUFFER_COMPLETE)
	{
		DBG_LOG("fbo %u\ntexture %u\nrbo %u", fbo, texture, rbo);

		SDL_Log("Framebuffer not complete: %x", res);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*	The horizontal screen radius is initially -1.0 - +1.0, but when projection
	 *	is applied, it might no longer be -1.0 - +1.0. The vertical screen radius will
	 *	always stay the same but the horizontal doesn't so adjust it */
	float oldHorizontal = horizontalRadius;
	horizontalRadius = static_cast <float> (size.x) / size.y;

	//	Recreate the Projection View matrix with the new frame dimensions
	projection = glm::perspective(glm::radians(90.0f), static_cast <float> (size.x) / size.y, 1.0f, 100.0f);
	Mat4 view = glm::lookAt(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(0, 1, 0));

	projection = projection * view;
	realSize = size;
}

Vec2 Frame::pointAt(Vec2 normalized)
{
	//DBG_LOG("pointAt (%.2f %.2f) -> (%.2f %.2f)", normalized.x, normalized.y, normalized.x * horizontalRadius, normalized.y);
	return Vec2(normalized.x * horizontalRadius, normalized.y);
}

Render Frame::render()
{
	//	So that the rendering is done at correct scale, set the viewport
	glViewport(0, 0, realSize.x, realSize.y);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glEnable(GL_DEPTH_TEST);

	DBG
	(
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	)

	return Render(projection, horizontalRadius);
}

void Frame::draw()
{
	static Mesh square(Mesh::Shape::Square);
	Shader& shader = Shader::get(Shader::Preset::Texture);

	shader.use();
	shader.setTransform(transform.transform);

	glBindTexture(GL_TEXTURE_2D, texture);
	square.draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
