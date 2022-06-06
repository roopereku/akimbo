#ifndef AKIMBO_TRANSFORM_HH
#define AKIMBO_TRANSFORM_HH

#include "Matrix4.hh"
#include "Vector3.hh"

namespace Akimbo {

class Transform
{
public:
	Transform() : transform(1.0f)
	{
	}

	void scale(Vec3 amount);
	void rotate(Vec3 amount);

	void scale(float x, float y, float z);
	void rotate(float x, float y, float z);

	Mat4 transform;
};

}

#endif
