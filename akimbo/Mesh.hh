#ifndef AKIMBO_MESH_HEADER
#define AKIMBO_MESH_HEADER

#include "Vector2.hh"
#include "Vector3.hh"

#include <array>
#include <vector>
#include <unordered_map>

class Mesh
{
public:
	enum class Shape
	{
		Square,
		Ball
	};

	Mesh(Shape shape);
	void draw();

private:
	struct Vertex
	{
		Vec3 position;
		Vec2 texture;
	};

	static void createSquare(std::vector <Vertex>& vertices, std::vector <unsigned>& indices);
	static void createBall(std::vector <Vec3>& vertices, std::vector <unsigned>& indices, int end);

	struct Buffers
	{
		unsigned vao;
		unsigned ebo;
		unsigned vbo;
		unsigned vertexCount = 0;
	};

	Buffers bufs;

	static Buffers loadMesh(Shape shape);
	static Buffers initMesh(std::vector <Vertex>& vertices, std::vector <unsigned>& indices);

	static std::array <Buffers, 2> shapeCache;
};

#endif
