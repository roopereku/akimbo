#include "Mesh.hh"

#include <GL/glew.h>
#include <SDL2/SDL_log.h>

#include <utility>
#include <cmath>

std::array <Mesh::Buffers, 2> Mesh::shapeCache;

void Mesh::createSquare(std::vector <Vertex>& vertices, std::vector <unsigned>& indices)
{
	vertices =
	{
		{ Vec3(1.0f, 1.0f, 0.0f), Vec2(1.0f, 1.0f) },
		{ Vec3(1.0f, -1.0f, 0.0f), Vec2(1.0f, 0.0f) },
		{ Vec3(-1.0f, -1.0f, 0.0f), Vec2(0.0f, 0.0f) },
		{ Vec3(-1.0f, 1.0f, 0.0f), Vec2(0.0f, 1.0f) }
	};

	indices =
	{
		0, 1, 3,
		1, 2, 3
	};
}

static Vec3 getPosition(unsigned angle)
{
	float radians = angle * M_PI / 180;
	return Vec3(cos(radians), sin(radians), 0.0f) * 0.5f;
};

void Mesh::createBall(std::vector <Vec3>& vertices, std::vector <unsigned>& indices, int end)
{
	unsigned skip = 10;
	unsigned vertexIndex = 2;
	unsigned index = 0;

	vertices.resize((end / skip) + 2);
	indices.resize((end / skip) * 3);

	vertices[0] = Vec3(0.0f, 0.0f, 0.0f);
	vertices[1] = getPosition(0);

	for(int i = skip; i <= end; i += skip)
	{
		vertices[vertexIndex] = getPosition(i);

		indices[index + 0] = 0;
		indices[index + 1] = vertexIndex - 1;
		indices[index + 2] = vertexIndex;

		vertexIndex++;
		index += 3;
	}
}

Mesh::Buffers Mesh::loadMesh(Shape shape)
{
	if(shapeCache[static_cast <size_t> (shape)].vertexCount > 0)
	{
		SDL_Log("Reusing shape");
		return shapeCache[static_cast <size_t> (shape)];
	}

	std::vector <Vertex> vertices;
	std::vector <unsigned> indices;

	switch(shape)
	{
		case Shape::Square: createSquare(vertices, indices); break;
		//case Shape::Ball: createBall(vertices, indices, 360); break;
		default: break;
	}

	shapeCache[static_cast <size_t> (shape)] = std::move(initMesh(vertices, indices));
	return shapeCache[static_cast <size_t> (shape)];
}

Mesh::Buffers Mesh::initMesh(std::vector <Vertex>& vertices, std::vector <unsigned>& indices)
{
	SDL_Log("%lu vertices %lu indices", vertices.size(), indices.size());
	Buffers b;

	glGenVertexArrays(1, &b.vao);
	glGenBuffers(1, &b.vbo);
	glGenBuffers(1, &b.ebo);

	glBindVertexArray(b.vao);

	glBindBuffer(GL_ARRAY_BUFFER, b.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	b.vertexCount = indices.size();

	return b;
}

Mesh::Mesh(Shape shape)
{
	bufs = loadMesh(shape);
}

void Mesh::draw()
{
	glBindVertexArray(bufs.vao);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, bufs.vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
