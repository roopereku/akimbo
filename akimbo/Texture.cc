#include "Texture.hh"
#include "Window.hh"
#include "Debug.hh"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/stb_image.h"

namespace Akimbo {

Texture::Texture(const std::string& path)
{
	DBG_LOG("Loading image '%s'", path.c_str());

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if(data)
	{
		//FIXME change to RGBA later
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		fprintf(stderr, "Unable to load texture: %s", path.c_str());
	}
}

Texture::~Texture()
{
}

Texture::Texture(Texture&& rhs)// : texture(rhs.texture)
{
	//rhs.texture = NULL;
}

}
